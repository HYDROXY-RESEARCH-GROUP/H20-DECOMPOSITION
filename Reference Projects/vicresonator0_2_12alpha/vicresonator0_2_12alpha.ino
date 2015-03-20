/*
   VIC Resonator written by Zissis aka zchiotis on open-source-energy.org forum.
   Downloaded from open-source-energy.org/?topic=1097.0 
   Version 0.2.10 beta changes made by firepinto
   Version 0.2.11 alpha changes made by firepinto 10/30/14
*/
#include <TimerOne.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, A0, A1, A2, A3);

#define TIMECTL_MAXTICKS 4294967295
#define TIMECTL_INIT 0
//Changed pins to match better with Pulsefire configuration.  Most importantly the LCD pins. - firepinto 11/2/14 
#define  PICKUP A5                                                //pickup coil is connected to pin A5 via voltage divider and a zener diode
#define  TONEOUT 9                                                //Output to the VIC primary coil
#define  GATEOUT 10                                               //Output pin for Gate signal
//#define  GATEDUTY A2                                              //potentiometer connected to A2 to set gating pulse duty
#define  SCAN 1                                                   //button for scan order is connected to pin D8
//#define  GATESET A1                                               //potentiometer connected to A1 pin to set gating frequency
#define  LOCKLED 8                                               //LED - indicator when the frequency is locked, pin D8
#define  SCANLED 12                                               //LED - indicator when scanning, pin D11                
#define  PEAKLED 13                                               //LED - indicates when pickup coil input A0 is at or near 5 volts. *Added by firepinto 10/26/14 
#define  SLRANGE  A4                                              //potentiometer connected to A3 to set the scale for manual adjustment buttons
#define  PLUS  3                                                 //Push Button for incrementing variable higher
#define  MINUS  4                                                //Push Button for incrementing variable lower 
#define  SELECTBTN  2                                             //Push Button for select function
// #define  GATELED 13                                            //LED - Gating indicator                               


int freq = 0;                                                     //Variable for Locked frequency
int freqmax = 5000;                                               //High end of freqency fine tune scale - firepinto 10/27/14
int freqmin = 500;                                                //Low end of freqency fine tune scale - firepinto 10/27/14
int hz = freqmin;
int scalerg = 0;                                                  //Variable for SLRANGE POT
int scale = 0;                                                    //Scale variable for manual frequency adjust buttons
int adjfreq = freq;                                               //Resulting frequency from auto scan and fine tune - firepinto 10/27/14
int volt = 0;
int vmax = 0;
int intval = 0;
int gateread = 0;
int gatef = 1;
int duty = 512;
int dutyP = 50;
int minusstate = 0;                                               //Variable for minus button manual frequency adjustment
int plusstate = 0;                                                //Variable for plus button manual frequency adjustment
int lastMstate = 0;                                               //last state for minus button
int lastPstate = 0;                                               //last state for plus button
int select = 0;                                                   //variable for select button
int lastselect = 0;                                               //last state of the select button
int dscan = 0;                                                    //time delay between frequency increments in milliseconds
int stpscna = 0;                                                  //Aborts scanning when equal to 1
int stpscnb = 0;                                                  //Aborts scanning when equal to 1
int menu = 0;                                                     //0=No field; 1=T1 field; 2=T3 field; 3=DY field; 4=DL field; 5=SR MAX field; 6=SR MIN field.  

unsigned long it = 0;
unsigned long itlcd = 0;
unsigned long reflcd = 250;                                       // LCD refresh rate mS
int odd = false;

byte lock[8] = {                                                  //custom character, it's a lock
	B01110,
	B10001,
	B10001,
	B11111,
	B11011,
	B11011,
	B11111,
	B00000
};
byte watermol[8] = {
	
	0b11000,
	0b11000,
	0b00111,
	0b00111,
	0b00111,
	0b11000,
	0b11000,
        0b00000
};
void setup()
{ 
  lcd.createChar(0, lock);
  lcd.createChar(1, watermol);
  lcd.begin(20, 4);
  lcd.print("   VIC RESONATOR");
  lcd.setCursor(0,1);
  lcd.print("   VER. 0.2.12a");                                  //print version to screen
  delay(5000);
 // Serial.begin(9600);
  pinMode(TONEOUT, OUTPUT); 
  pinMode(GATEOUT, OUTPUT);
 // pinMode(GATEDUTY, INPUT);  
  pinMode(PICKUP, INPUT);                                        //initializing the pins
  pinMode(SCAN, INPUT);
 // pinMode(GATESET, INPUT);
  pinMode(SLRANGE, INPUT);                                       //firepinto - 10/27/14
  pinMode(LOCKLED, OUTPUT);                                      //firepinto - 10/27/14
  pinMode(SCANLED, OUTPUT);                                      //firepinto - 10/27/14
  pinMode(PEAKLED, OUTPUT);                                      //firepinto - 10/27/14
  pinMode(PLUS, INPUT);                                          //firepinto - 10/27/14
  pinMode(MINUS, INPUT);                                         //firepinto - 10/27/14
  pinMode(SELECTBTN,  INPUT);

//  pinMode(GATELED, OUTPUT);                                    //unused as of ver. 0.2.10a 
  Timer1.initialize(1000000);
}

void loop()
{   
vmax = 0;                                                        //comment if you want to keep the best frequency of all scans 
intval = 0;                                                      //comment if you want to see the frequency found interval in all scans
noTone(TONEOUT);                                                 // used to have LOCKLED pin
digitalWrite(LOCKLED, LOW);
Timer1.stop();
digitalWrite(GATEOUT, LOW);
//digitalWrite(GATELED, LOW);                                    //unused as of ver. 0.2.10a
lcd.clear();
lcd.print("   SCANNING FROM:   ");
digitalWrite(SCANLED, HIGH);
lcd.setCursor(0,1);
lcd.print("        TO       Hz");
lcd.setCursor(0,2);
lcd.print("SN=      Hz");
lcd.setCursor(12,2);
lcd.print("DL=");
lcd.print(dscan);
lcd.setCursor(0,3);
lcd.print("T1=      Hz");
lcd.setCursor(12,3);
lcd.print("CT=");
hz = freqmin;
//for (hz=500; hz<=1000; hz=hz+1)                                 //start from 500hz to 18khz to oscillate the circuit
 do
   {
  hz+=1;
  tone(TONEOUT,hz);                                               //will send a tone at first
  delay(1);                                                       //wait for a millisec
 
  volt = analogRead(PICKUP);                                      //then read the voltage
  if (volt > 818)                                                 //If pick-up coil voltage is greater than 4 volts
    {
    digitalWrite(PEAKLED, HIGH);                                  //turn on peak LED 
    }
     else
    {
    digitalWrite(PEAKLED, LOW);                                   //turn off peak LED
    }
  if (vmax < volt)                                                //if there is a resonant point voltage should have the highest value on this frequency
  {
    vmax = volt;                                                  //store as the best voltage
    freq = hz;                                                    //remember that frequency
    intval = intval++;                                            //times found a nice frequency interval, is showing during scan on the left of the lcd
    lcd.setCursor(15,3);
    lcd.print(intval);
    lcd.setCursor(3,2);
    lcd.print("     ");
    lcd.setCursor(3,3);
    lcd.print(freq); 
  }
  lcd.setCursor(3,2);
  lcd.print(hz);
  lcd.setCursor(2,1);
  lcd.print(freqmin);
  lcd.setCursor(11,1);
  lcd.print(freqmax);
   if (hz == freqmax)
     {
      stpscna=2;
     }
    else
   { 
   if (digitalRead(SELECTBTN) == HIGH)
     {
     stpscna=3;
     stpscnb=3;
     }
   } 
  delay(dscan);
   }while (stpscna < 1);

 //for (hz=1000; hz>=500; hz=hz-1)                                //do the same for a descent scan
  lcd.setCursor(11,1);                                            //Clears text fields for frequency scan range downward scan
  lcd.print("     ");
  lcd.setCursor(2,1);
  lcd.print("     ");
 do
   {
   hz-=1;
 // lcd.setCursor(5,1);
  // lcd.print("     ");
  // lcd.print(hz);
      tone(TONEOUT,hz);   
    delay(1);

    volt = analogRead(PICKUP);
    if (volt > 818)                                               // *Added by firepinto 10/26/14
    {
    digitalWrite(PEAKLED, HIGH);
    }
     else
    {
    digitalWrite(PEAKLED, LOW);
    }
    if (vmax < volt)
    {
      vmax = volt;
      freq = hz;
      adjfreq = freq;
      intval = intval++  ;
      lcd.setCursor(15,3);
      lcd.print(intval);
      lcd.setCursor(3,2);  
      lcd.print("     ");
      lcd.setCursor(3,3);
      lcd.print(freq);
    }
     if (hz < 10000)
    {
      lcd.setCursor(5,2);
      lcd.print("   ");
    } 
  lcd.setCursor(3,2);
  lcd.print(hz);
  lcd.setCursor(2,1);
  lcd.print(freqmax);
  lcd.setCursor(11,1);
  lcd.print(freqmin);

   if (hz == freqmin)
     {
      stpscnb=2;
     }
    else
   { 
   if (digitalRead(SELECTBTN) == HIGH)
     {
     stpscnb=3;
     }
   }

  delay(dscan);
   }while (stpscnb < 1);
  stpscna = 0;
  stpscnb = 0;
  digitalWrite(SCANLED, LOW);
  tone(TONEOUT,freq);                                             //output the frequency found with higher voltage reading
  //tone(LOCKLED, (4));                                           //LOCKLED isn't on a PWM pin - firepinto 10/27/14
 /* lcd.clear();
  lcd.print("RESONANCE FOUND");                                   //Removed because it is redundant now - firepinto 11/1/14
  lcd.setCursor(4, 1);
  lcd.print("@");
  lcd.setCursor(6, 1);                                            //printing to LCD
  lcd.print(freq);
  lcd.setCursor(12, 1);
  lcd.print("Hz");
  delay(1500);                                                    //Changed from delay(2500); to delay(1500); - firepinto 10/26/14
  */
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("WAITING FOR");
  lcd.setCursor(0, 1);
  lcd.print("STABILIZATION...");
  delay(2500);                                                    //waiting for a stabilizing time for the circuit, comment to avoid *Changed from delay(5500); to delay(2500); - firepinto 10/26/14
  volt = analogRead(PICKUP);                                      //read again the voltage from the pickup coil
    if (volt > 818)                                               // *Added by firepinto 10/26/14
    {
    digitalWrite(PEAKLED, HIGH);
    }
     else
    {
    digitalWrite(PEAKLED, LOW);
    }
  if (volt > vmax-51)                                             //check if read voltage is less than 10% of the best voltage found
   {
   lcd.clear();                                                   //if not, scan will start again
   lcd.setCursor(3,0);
   lcd.print("FREQUENCY");
   lcd.setCursor(1,1);
   lcd.write(byte(0));
   lcd.setCursor(3,1);
   lcd.print("  LOCKED");
   //noTone(SCANLED);                                             //LOCKLED pin doesn't have PWM - firepinto 10/27/14
   digitalWrite(LOCKLED, HIGH);
  
   delay(1000);                                                   //Changed from delay(2000); to delay(1000); - firepinto 10/26/14
  }
  
                                              
  lcd.clear();
  lcd.setCursor(0,0);                                             //Move to digit 0 row 0
  lcd.print("T1=");                                               //Pulse frequency title "T1=" with units label "Hz"
  lcd.setCursor(9,0);                                             //Move to digit 9 row 0
  lcd.print("Hz");
  lcd.setCursor(13,0);                                            //Move to digit 13 row 0
  lcd.print("VT=");                                               //Pick-up coil voltage title "VT="
  lcd.setCursor(0,1);                                             //same idea continued below 
  lcd.print("T3=");
  lcd.setCursor(9,1);                                             //Move to digit 9 row 1
  lcd.print("Hz");
  lcd.setCursor(13,1);
  lcd.print("DY=");
  lcd.setCursor(19,1);
  lcd.print("%");
  lcd.setCursor(0,2); 
  lcd.print("LK=");
  lcd.setCursor(9,2); 
  lcd.print("Hz");
  lcd.setCursor(13,2);
  lcd.print("DL=");
  lcd.setCursor(0,3);
  lcd.print("SR=");
  lcd.setCursor(8,3);
  lcd.print(">");
  lcd.setCursor(15,3);
  lcd.print("S");
  adjfreq = freq;                                                 //sets adjustable frequency equal to the locked frequency
  //========================================================================================================
  while (digitalRead(SCAN) == LOW)                                //until the scan button is pressed, do the following
  {  
  tone(TONEOUT,adjfreq);                                          //turns on pulse signal to pin 9 with adjustable frequency
  //gateread = analogRead(GATESET);                               //reads Gate frequency potentiometer and sets the variable
 // duty = analogRead(GATEDUTY);                                  //read the gating set value from pin A1
  scalerg = analogRead(SLRANGE);                                  //reads the scale for manual frequency adjustment buttons from the potentiometer and sets the variable
 // gatef = map (gateread, 0, 1023, 1, 120);                      //limit the gating frequency from 1 to 120 hz
  scale = map (scalerg, 0, 1023, 1, 1000);                        //limit the gating frequency from 1 to 120 hz ---fp
  //dutyP = map (duty, 0, 1023, 100, 0);                          //translate T(miliseconds) into f(Hz) for gating frequency
  duty = map (dutyP, 100, 0, 0, 1023);                            //trying this reversed since setting display direclty through pushbuttons
  Timer1.pwm(GATEOUT, duty, 1000000/gatef);                       //turns on Gating signal to pin 10
  volt = analogRead(PICKUP);                                      //read the voltage on the VIC           *Needed to uncomment this line for the pick up coil voltage to be read during gating - firepinto 10/25/14
  if (volt > 818)                                                 //If pickup coil voltage is over 4 volts at pin, light LED. *Added by firepinto 10/26/14
     {
     digitalWrite(PEAKLED, HIGH);                                 //Turn ON pick-up coil peak voltage LED
     }
   else
     {
     digitalWrite(PEAKLED, LOW);                                  //Turn OFF pick-up coil peak voltage LED
     }  
 //__________________________________________________________________________________________
 select = digitalRead(SELECTBTN);       
 if (select == HIGH)
    {
    delay(300);  
    if (menu < 6)
       {
       menu+=1;
       }
       else
       {
       menu=0;
       }
    }
//  lcd.setCursor(11,0);  
// lcd.print(menu); 
 if (menu == 1)//-------BEGIN MASSIVE MENU IF STATEMENT--------------------------------------------------------------
    {  //---------------BEGIN T1 MENU CODE---------------------------------------------------------------------------  
       lcd.setCursor(2,0);
       lcd.write(byte(1)); 
       plusstate = digitalRead(PLUS);                             //reads frequency plus push button and sets the variable to its value
       if (adjfreq < 24390)                                       //sets maximum frequency to 24390 through the manual "plus" push button
          { 
          if (lastPstate != 1)                                    //if last state of plus button does not equal 1
             {
             if (plusstate == HIGH)                               //if plus button state is HIGH
                {
                adjfreq+=scale;                                   //Add scale frequency to adjustable frequency
                digitalWrite(SCANLED, HIGH);                      //Turn on Scan LED
                lastPstate = plusstate;                           //set plus button last state variable
                delay(100);                                       //100 millisecond delay for button debounce (there may be a better option than this)
                }
              else                                                //if not
               {
               digitalWrite(SCANLED, LOW);                        //Turn off Scan LED
               lastPstate = plusstate;                            //set plus button last state variable 
               }
             }   
           else                                                   //if not
             {
             lastPstate = plusstate;                              //set plus button last state variable
             }
          }
          minusstate = digitalRead(MINUS);                        //reads frequency increase push button and sets the variable to its value
          if (adjfreq > scale)                                    //sets minimum frequency to the scale frequency through the manual "minus" push button
             {
             if (lastMstate != 1)                                 //if last state of minus button does not equal 1
                {
                if (minusstate == HIGH)                           //if minus button state is HIGH
                   {
                   adjfreq-=scale;                                //Subtract scale frequency from adjustable frequency
                   digitalWrite(SCANLED, HIGH);                   //Turn on Scan LED
                   lastMstate = minusstate;                       //set minus button last state variable
                   delay(100);                                    //100 millisecond delay for button debounce (there may be a better option than this)
                   }
                 else                                             //if not
                   {
                   digitalWrite(SCANLED, LOW);                    //Turn off Scan LED
                   lastMstate = minusstate;                       //set minus button last state variable 
                   }
                }
              else                                                //if not
                {
                lastMstate = minusstate;                          //set minus button last state variable
                }
              }
    } //------------------END T1 MENU CODE------------------------------------------------------------

     //------------------BEGIN T3 MENU CODE----------------------------------------------------------
    if (menu == 2)
       {      
       lcd.setCursor(2,1);
       lcd.write(byte(1));
       lcd.setCursor(2,0);
       lcd.print("=");
       plusstate = digitalRead(PLUS);                             //reads plus push button and sets the variable to its value
       if (gatef < 120)                                           //sets maximum gate frequency to 120 through the manual "plus" push button
          { 
          if (lastPstate != 1)                                    //if last state of plus button does not equal 1
             {
             if (plusstate == HIGH)                               //if plus button state is HIGH
                {
                gatef+=scale;                                     //Add scale frequency to adjustable frequency
                digitalWrite(SCANLED, HIGH);                      //Turn on Scan LED
                lastPstate = plusstate;                           //set plus button last state variable
                delay(100);                                       //100 millisecond delay for button debounce (there may be a better option than this)
                }
              else                                                //if not
                {
                digitalWrite(SCANLED, LOW);                       //Turn off Scan LED
                lastPstate = plusstate;                           //set plus button last state variable 
                }
             }   
           else                                                   //if not
             {
             lastPstate = plusstate;                              //set plus button last state variable
             }
          }
          minusstate = digitalRead(MINUS);                        //reads frequency increase push button and sets the variable to its value
          if (gatef > scale)                                      //sets minimum frequency to the scale frequency through the manual "minus" push button
             {
             if (lastMstate != 1)                                 //if last state of minus button does not equal 1
                {
                if (minusstate == HIGH)                           //if minus button state is HIGH
                   {
                   gatef-=scale;                                  //Subtract scale from adjustable frequency
                   digitalWrite(SCANLED, HIGH);                   //Turn on Scan LED
                   lastMstate = minusstate;                       //set minus button last state variable
                   delay(100);                                    //100 millisecond delay for button debounce (there may be a better option than this)
                   }
                 else                                             //if not
                   {
                   digitalWrite(SCANLED, LOW);                    //Turn off Scan LED
                   lastMstate = minusstate;                       //set minus button last state variable 
                   }
                 }
               else                                               //if not
                 {
                 lastMstate = minusstate;                         //set minus button last state variable
                 }
              }
       }//----------------------END T3 MENU CODE-------------------------------------------

        //------------------BEGIN DY MENU CODE---------------------------------------------------------- 
       if (menu == 3)
          {
          lcd.setCursor(15,1);
          lcd.write(byte(1));
          lcd.setCursor(2,1);
          lcd.print("=");
          plusstate = digitalRead(PLUS);                          //reads plus push button and sets the variable to its value
          if (dutyP < 100)                                        //sets maximum gate duty to 100% through the manual "plus" push button
             { 
             if (lastPstate != 1)                                 //if last state of plus button does not equal 1
                {
                if (plusstate == HIGH)                            //if plus button state is HIGH
                   {
                   dutyP+=scale;                                  //Add scale frequency to adjustable frequency
                   digitalWrite(SCANLED, HIGH);                   //Turn on Scan LED
                   lastPstate = plusstate;                        //set plus button last state variable
                   delay(100);                                    //100 millisecond delay for button debounce (there may be a better option than this)
                   }
                 else                                             //if not
                   {
                   digitalWrite(SCANLED, LOW);                    //Turn off Scan LED
                   lastPstate = plusstate;                        //set plus button last state variable 
                   }
                }   
              else                                                //if not
                {
                lastPstate = plusstate;                           //set plus button last state variable
                }
             }
             minusstate = digitalRead(MINUS);                     //reads frequency increase push button and sets the variable to its value
             if (dutyP > scale)                                   //sets minimum frequency to the scale frequency through the manual "minus" push button
                {
                if (lastMstate != 1)                              //if last state of minus button does not equal 1
                   {
                   if (minusstate == HIGH)                        //if minus button state is HIGH
                      {
                      dutyP-=scale;                               //Subtract scale from adjustable frequency
                      digitalWrite(SCANLED, HIGH);                //Turn on Scan LED
                      lastMstate = minusstate;                    //set minus button last state variable
                      delay(100);                                 //100 millisecond delay for button debounce (there may be a better option than this)
                      }
                    else                                          //if not
                      {
                      digitalWrite(SCANLED, LOW);                 //Turn off Scan LED
                      lastMstate = minusstate;                    //set minus button last state variable 
                      }
                   }
                 else                                             //if not
                   {
                   lastMstate = minusstate;                       //set minus button last state variable
                   }
                }
           }
         //----------------------END DY MENU CODE-------------------------------------------

         //------------------BEGIN DL MENU CODE---------------------------------------------------------- 
        if (menu == 4)
           {
           lcd.setCursor(15,2);
           lcd.write(byte(1));
           lcd.setCursor(15,1);
           lcd.print("=");
           plusstate = digitalRead(PLUS);                         //reads plus push button and sets the variable to its value
           if (dscan < 1000)                                      //sets maximum delay for scan to 1000 milliseconds through the manual "plus" push button
              { 
              if (lastPstate != 1)                                //if last state of plus button does not equal 1
                 {
                 if (plusstate == HIGH)                           //if plus button state is HIGH
                    {
                    dscan+=scale;                                 //Add scale to scan delay
                    digitalWrite(SCANLED, HIGH);                  //Turn on Scan LED
                    lastPstate = plusstate;                       //set plus button last state variable
                    delay(100);                                   //100 millisecond delay for button debounce (there may be a better option than this)
                    }
                  else                                            //if not
                    {
                    digitalWrite(SCANLED, LOW);                   //Turn off Scan LED
                    lastPstate = plusstate;                       //set plus button last state variable 
                    }
                 }   
               else                                               //if not
                 {
                 lastPstate = plusstate;                          //set plus button last state variable
                 }
              }
              minusstate = digitalRead(MINUS);                    //reads frequency increase push button and sets the variable to its value
              if (dscan > scale)                                  //sets minimum frequency to the scale frequency through the manual "minus" push button
                 {
                 if (lastMstate != 1)                             //if last state of minus button does not equal 1
                    {
                    if (minusstate == HIGH)                       //if minus button state is HIGH
                       {
                       dscan-=scale;                              //Subtract scale from scan delay
                       digitalWrite(SCANLED, HIGH);               //Turn on Scan LED
                       lastMstate = minusstate;                   //set minus button last state variable
                       delay(100);                                //100 millisecond delay for button debounce (there may be a better option than this)
                       }
                     else                                         //if not
                       {
                       digitalWrite(SCANLED, LOW);                //Turn off Scan LED
                       lastMstate = minusstate;                   //set minus button last state variable 
                       }
                    }
                  else                                            //if not
                    {
                    lastMstate = minusstate;                      //set minus button last state variable
                    }
                 }
            }
          //----------------------END DL MENU CODE-------------------------------------------

          //------------------BEGIN SR MAX MENU CODE---------------------------------------------------------- 
         if (menu == 5)
            {
            lcd.setCursor(2,3);
            lcd.write(byte(1));
            lcd.setCursor(15,2);
            lcd.print("=");
            plusstate = digitalRead(PLUS);                        //reads plus push button and sets the variable to its value
            if (freqmax < 24390)                                  //sets maximum delay for scan to 1000 milliseconds through the manual "plus" push button
               { 
               if (lastPstate != 1)                               //if last state of plus button does not equal 1
                  {
                  if (plusstate == HIGH)                          //if plus button state is HIGH
                     {
                     freqmax+=scale;                              //Add scale to scan delay
                     digitalWrite(SCANLED, HIGH);                 //Turn on Scan LED
                     lastPstate = plusstate;                      //set plus button last state variable
                     delay(100);                                  //100 millisecond delay for button debounce (there may be a better option than this)
                     }
                   else                                           //if not
                     {
                     digitalWrite(SCANLED, LOW);                  //Turn off Scan LED
                     lastPstate = plusstate;                      //set plus button last state variable 
                     }
                  }   
                else                                              //if not
                  {
                  lastPstate = plusstate;                         //set plus button last state variable
                  }
               }
               minusstate = digitalRead(MINUS);                   //reads frequency increase push button and sets the variable to its value
               if (freqmax > scale)                               //sets minimum frequency to the scale frequency through the manual "minus" push button
                  {
                  if (lastMstate != 1)                            //if last state of minus button does not equal 1
                     {
                     if (minusstate == HIGH)                      //if minus button state is HIGH
                        {
                        freqmax-=scale;                           //Subtract scale from scan delay
                        digitalWrite(SCANLED, HIGH);              //Turn on Scan LED
                        lastMstate = minusstate;                  //set minus button last state variable
                        delay(100);                               //100 millisecond delay for button debounce (there may be a better option than this)
                        }
                      else                                        //if not
                        {
                        digitalWrite(SCANLED, LOW);               //Turn off Scan LED
                        lastMstate = minusstate;                  //set minus button last state variable 
                        }
                     }
                   else                                           //if not
                     {
                     lastMstate = minusstate;                     //set minus button last state variable
                     }
                  }
             }
           //----------------------END SR MAX MENU CODE-------------------------------------------

           //------------------BEGIN SR MIN MENU CODE---------------------------------------------------------- 
          if (menu == 6)
             {
             lcd.setCursor(8,3);
             lcd.write(byte(1));
             lcd.setCursor(2,3);
             lcd.print("=");
             plusstate = digitalRead(PLUS);                       //reads plus push button and sets the variable to its value
             if (freqmin < 24390)                                 //sets maximum delay for scan to 1000 milliseconds through the manual "plus" push button
                { 
                if (lastPstate != 1)                              //if last state of plus button does not equal 1
                   {
                   if (plusstate == HIGH)                         //if plus button state is HIGH
                      {
                      freqmin+=scale;                             //Add scale to scan delay
                      digitalWrite(SCANLED, HIGH);                //Turn on Scan LED
                      lastPstate = plusstate;                     //set plus button last state variable
                      delay(100);                                 //100 millisecond delay for button debounce (there may be a better option than this)
                      }
                    else                                          //if not
                      {
                      digitalWrite(SCANLED, LOW);                 //Turn off Scan LED
                      lastPstate = plusstate;                     //set plus button last state variable 
                      }
                   }   
                 else                                             //if not
                   {
                   lastPstate = plusstate;                        //set plus button last state variable
                   }
                }
                minusstate = digitalRead(MINUS);                  //reads frequency increase push button and sets the variable to its value
                if (freqmin > scale)                              //sets minimum frequency to the scale frequency through the manual "minus" push button
                   {
                   if (lastMstate != 1)                           //if last state of minus button does not equal 1
                      {
                      if (minusstate == HIGH)                     //if minus button state is HIGH
                         {
                         freqmin-=scale;                          //Subtract scale from scan delay
                         digitalWrite(SCANLED, HIGH);             //Turn on Scan LED
                         lastMstate = minusstate;                 //set minus button last state variable
                         delay(100);                              //100 millisecond delay for button debounce (there may be a better option than this)
                         }
                       else                                       //if not
                         {
                         digitalWrite(SCANLED, LOW);              //Turn off Scan LED
                         lastMstate = minusstate;                 //set minus button last state variable 
                         }
                      }
                    else                                          //if not
                      {
                      lastMstate = minusstate;                    //set minus button last state variable
                      }
                   }
              }
            //----------------------END SR MIN MENU CODE-------------------------------------------
    if (menu == 0)
       {
       lcd.setCursor(8,3);
       lcd.print(">");
       }      
//___________________BEGIN HARD LIMITS CODE____________________________________________________________________________________
if (adjfreq < 31)                                                 //blocks the minus push button from going lower than 31 Hz
   {
   adjfreq = 31;
   }
if (adjfreq > 24390)                                              //blocks the plus push button from going higher than 24390 Hz
   {
   adjfreq = 24390;
   }
if (gatef < 1)                                                    //blocks the minus push button from going lower than 1 Hz
   {
   gatef = 1;
   }
if (gatef > 120)                                                  //blocks the plus push button from going higher than 120 Hz
   {
   gatef = 120;
   }
if (dutyP < 1)                                                    //blocks the minus push button from going lower than 1%
   {
   dutyP = 1;
   }
if (dutyP > 100)                                                  //blocks the plus push button from going higher than 100%
   {
   dutyP = 100;
   }
if (dscan < 0)                                                    //blocks the minus push button from going lower than 0 milliseconds
   {
   dscan = 0;
   }
if (dscan > 5000)                                                 //blocks the plus push button from going higher than 5000 milliseconds
   {
   dscan = 5000;
   }   
if (freqmax < 31)                                                 //blocks the minus push button from going lower than 31 Hz
   {
   freqmax = 31;
   }
if (freqmax > 24390)                                              //blocks the plus push button from going higher than 24390 Hz
   {
   freqmax = 24390;
   }
if (freqmin < 31)                                                 //blocks the minus push button from going lower than 31 Hz
   {
   freqmin = 31;
   }
if (freqmin > 24390)                                              //blocks the plus push button from going higher than 24390 Hz
   {
   freqmin = 24390;
   }  
//______________________________________________________________________________________________________     
double vdisp = volt*(5.0/1023.0);                                 //scale digital signal to analog 0.0 - 5.0 volts
   if (adjfreq == 0)                                              //resets adjustable frequency to locked frequency if it is zero
      {
      adjfreq = freq;
      }
   if (adjfreq != freq)                                           //if adjustable frequency does not equal locked frequency.
       {
       digitalWrite(LOCKLED, LOW);                                //then turn off Lock LED
       }
     else                                                         //if not
       {
       digitalWrite(LOCKLED, HIGH);                               //turn on Lock LED
       }
   if (istime(&itlcd,reflcd))                                     //Original ver. 0.2.10a code
      {                                                           //Reorganized LCD and relabeled titles to Stanley Meyer terminology (May want to print titles elsewhere so they don't need to continually refresh and slow down the program, if possible)
      lcd.setCursor(3,0);                                         //Move to digit 3 row 0
      lcd.print("     ");                                         //Overwrites with spaces to clear digits
      lcd.setCursor(3,0);                                         //Move to digit 3 row 0
      lcd.print(adjfreq);                                         //Adjustable frequency 
      lcd.setCursor(16,0);                                        //Move to digit 16 row 0
      lcd.print("    ");                                          //Overwrites with spaces to clear digits
      lcd.setCursor(16,0);                                        //Move to digit 16 row 0
      lcd.print(vdisp);                                           //Pick-up coil voltage
      lcd.setCursor(3,1);
      lcd.print("   ");
      lcd.setCursor(3,1);
      lcd.print(gatef);
      lcd.setCursor(16,1);
      lcd.print("   ");
      lcd.setCursor(16,1);
      lcd.print(dutyP);
      lcd.setCursor(3,2); 
      lcd.print("     ");
      lcd.setCursor(3,2); 
      lcd.print(freq);
      lcd.setCursor(16,2);
      lcd.print("    ");
      lcd.setCursor(16,2);
      lcd.print(dscan);
      lcd.setCursor(3,3);
      lcd.print("     ");
      lcd.setCursor(3,3);             
      lcd.print(freqmax);
      lcd.setCursor(9,3);
      lcd.print("     ");
      lcd.setCursor(9,3);             
      lcd.print(freqmin);
      lcd.setCursor(16,3);
      lcd.print("    ");
      lcd.setCursor(16,3);
      lcd.print(scale); 
      }
 if (volt < vmax-51)                                              //after frequency has been locked and gating is on, whenever the voltage drops over 10% of the last best voltage found
    {
    if (adjfreq == freq)                                          //Disables the auto scan feature commented above when the adjustable frequency is not equal to the locked frequency
       {
       break;                                                     //scan will accur again by itself
       }
    }
}//_________________END OF WHILE_________________________________________________________
}//__________________END OF VOID LOOP__________________________________________________
int istime(unsigned long *timemark, unsigned long timeinterval)   //Code below all original from ver. 0.2.10a
{
  unsigned long timecurrent;
  unsigned long timeelapsed;
  int result = false;
  timecurrent=millis();
  
  if (timecurrent<*timemark)
  {
    timeelapsed = (TIMECTL_MAXTICKS-*timemark)*timecurrent;
  }
  else 
  {
    timeelapsed = timecurrent-*timemark;
  }
  if (timeelapsed>=timeinterval)
  {
    *timemark = timecurrent;
    result = true;
  }
  return(result);
}

