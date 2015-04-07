
/*
  H2OtoHHO.cpp
*/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// include this library's description file
#include <LiquidCrystal.h>
//#include <Tone.h>
#include "pitches.h"
#include <LCDKeypad.h>
#include <DFR_Key.h>
#include <AD9850.h>
#include "H2OtoHHO.h"
//#include <H2OtoHHO.h>
// ensure this library description is only included once



/* CREATE DFR Keypad CLASS INSTANCE */
//DFR_Key keypad;
//---------------------------------------------



/* Define Locale Variables */
//int FuncKey = 0;
//String keyString = "";
//int F_Resonace = 4243;                                                  //Variable for Locked frequency
//int hz = freqmin;
//int scalerg = 0;                                                  //Variable for SLRANGE POT
//int scale = 0;                                                    //Scale variable for manual frequency adjust buttons
//int adjfreq = freq;                                               //Resulting frequency from auto scan and fine tune - firepinto 10/27/14
//int volt = 0;
//int vmax = 0;
//int intval = 0;
//int gateread = 0;
//int gatef = 1;
//int duty = 512;
//int dutyP = 50;
//int minusstate = 0;                                               //Variable for minus button manual frequency adjustment
//int plusstate = 0;                                                //Variable for plus button manual frequency adjustment
//int lastMstate = 0;                                               //last state for minus button
//int lastPstate = 0;                                               //last state for plus button
//int select = 0;                                                   //variable for select button
//int lastselect = 0;                                               //last state of the select button
//int dscan = 0;                                                    //time delay between frequency increments in milliseconds
//int stpscna = 0;                                                  //Aborts scanning when equal to 1
//int stpscnb = 0;                                                  //Aborts scanning when equal to 1
//int menu = 0;                                                     //0=No field; 1=T1 field; 2=T3 field; 3=DY field; 4=DL field; 5=SR MAX field; 6=SR MIN field.  

//unsigned long it = 0;
//unsigned long itlcd = 0;
//unsigned long reflcd = 250;                                       // LCD refresh rate mS
//int odd = false;
//---------------------------------------------


byte c_right[8] = {
  B00000,
  B00100,
  B00010,
  B11111,
  B11111,
  B00010,
  B00100,
  B00000,
};

byte c_up[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
};

byte c_down[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
};

byte c_left[8] = {
  B00000,
  B00100,
  B01000,
  B11111,
  B11111,
  B01000,
  B00100,
  B00000,
};

byte c_select[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
};

byte custom_lock[8] = {                //custom character, it's a lock
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11111,
  B00000
};

byte custom_watermol[8] = {           //custom character, it's a Water Molecule
  B11000,
  B11000,
  B00111,
  B00111,
  B00111,
  B11000,
  B11000,
  B00000
};



H2OtoHHO::H2OtoHHO()
{
  /* CREATE LCDKeypad CLASS INSTANCES */
  screen = new LCDKeypad();
  //---------------------------------------------
  
  /* CREATE DFR_Key CLASS INSTANCES */
  ctrls = new DFR_Key();
  //---------------------------------------------
  
  /* CREATE AD9850 CLASS INSTANCES */
  gate = new AD9850(DDS0_CLK_Pin, DDS0_FQ_Pin, DDS0_DATA_Pin);                   // w_clk, fq_ud, Sdata
  pulse = new AD9850(DDS1_CLK_Pin, DDS1_FQ_Pin, DDS1_DATA_Pin);                  // w_clk, fq_ud, Sdata
  //---------------------------------------------
  
  /* Initialize AD9850 CLASS INSTANCES */
  screen->createChar(CURSOR_SELECT, c_select);
  screen->createChar(CURSOR_LEFT, c_left);
  screen->createChar(CURSOR_UP, c_up);
  screen->createChar(CURSOR_DOWN, c_down);
  screen->createChar(CURSOR_RIGHT, c_right);
  screen->createChar(CUSTOM_WATER_MOLECULE, custom_watermol);
  screen->createChar(CUSTOM_LOCK, custom_lock);    
}



/*
H2OtoHHO::LoadSymbols()
{
	createChar(CURSOR_RIGHT, c_right);
	createChar(CURSOR_UP, c_up);
	createChar(CURSOR_DOWN, c_down);
	createChar(CURSOR_LEFT, c_left);
	createChar(CURSOR_SELECT, c_select);
	createChar(CUSTOM_LOCK, custom_lock);
	createChar(CUSTOM_WATER_MOLECULE, custom_watermol);
}
*/


/* Scans Resonant Frequency */
int H2OtoHHO::ResonanceScan()
{
  uint32_t lockFreq = 0;
  
  screen->clear();
  screen->print("  SCANNING RANGE....  ");
   
  // Sweep frequency from 'F_Scan_min' to 'F_Scan_max' 
  for (uint32_t i = SCAN_FREQ_MIN; i < SCAN_FREQ_MAX; i++)
  {        
    screen->setCursor(3,1);
    screen->print(i);
    screen->print(" Hz  ");
    
    gate->setfreq(i);
    pulse->setfreq(i*10);
  }
  
  delay(200);
  lockFreq = 4243;
  screen->print(" ");
  screen->write(CUSTOM_LOCK);
  screen->print(" ");
  screen->print( lockFreq );
  screen->print(" Hz  ");  
  delay(2000);
  
  return lockFreq;
}
//---------------------------------------------



/* Main Menu Function  */
int H2OtoHHO::MainMenu()
{
  int k = 0, exitCode = -1, SelectedItem = 0, keypress= 0;
  String MainItems[4] = {
    " 1. Exit Menu!",
    " 2. Re-Scan Freq.",
    " 3. [Option #2]",
    " 4. Debug Mode" };
    
  
  do
  {
    //keypress = H2OtoHHO::button();
    
    switch ( screen->button() ) 
    {
      //case KEYPAD_RIGHT:
      //  break;
        
      case KEYPAD_UP:
          if ( SelectedItem > 0 )
          {
            SelectedItem--;
            screen->setCursor(0,1);
            screen->print( MainItems[SelectedItem] );
            delay(2000);
          }
          //else 
           // buzzer.play( NOTE_C4, BuzzerShortTone );
            
          //exitCode = 0;
        break;
        
      case KEYPAD_DOWN:
          if ( SelectedItem < 4 )
          {
            SelectedItem++;
            screen->setCursor(0,1);
            screen->print( MainItems[SelectedItem] );
            delay(2000);
          }
          //else
            //buzzer.play( NOTE_C4, BuzzerShortTone );
            
             //exitCode = 0;
        break;
        
      //case KEYPAD_LEFT:
      //  break;
        
      case KEYPAD_SELECT:
          screen->begin(16, 2);
          screen->clear();
          screen->print("     MAIN");
          screen->setCursor(0,1);
          screen->print("     MENU");
          delay(3000);
          
          for (k=0;k<16;k++)
          {
            screen->scrollDisplayLeft();
            delay(200);
          }
          
          MainMenu();
          
        break;
        
      default:
        exitCode = 0;
    }
    
  } while (exitCode!=-1);
  
  return exitCode;  
}
//---------------------------------------------


/* Updates Display upon Keypress */
int H2OtoHHO::UpdateKeypress(int keyPress)
{
  //if (keyPress != KEYPAD_NONE)
  //{
    screen->clear();
    screen->setCursor(0, 0);
    screen->print("Current Key:");
    screen->setCursor(0, 1);
    screen->print(keyPress);
    screen->print(" => ");
    screen->print(analogRead(0));
    screen->print(", ");
    screen->print( screen->button() );
    delay(1000);
  //}
  return 0;
}
//---------------------------------------------


