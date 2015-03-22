/*
H2O to HHO Generator v0.2
Written by R.E.D.

Hardware:
--------------------------------------------------
  1. Sainsmart Arduino Due V1.0
  2. Sainsmart LCD Shield for Arduino V1.0
  

Displays the currently pressed key on the LCD screen.

Key Codes (in left-to-right order):

None   - 0
Select - 1
Left   - 2
Up     - 3
Down   - 4
Right  - 5

*/
#include "H2OtoHHO.h"


//Pin assignments for SainSmart LCD Keypad Shield
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
#define MINVAL 1
#define MAXVAL 1000

LCDKeypad lcd;
H2OtoHHO loadSymbols(lcd);
//---------------------------------------------


/* CREATE DFR Keypad CLASS INSTANCE */
DFR_Key keypad;
//---------------------------------------------


/* I\O PIN MAPPING AD9850 MODULE 0- Gate Frequency Generator  */
const int DDS0_CLK_Pin = 22;
const int DDS0_FQ_Pin = 23;
const int DDS0_DATA_Pin = 24;
const int DDS0_RESET_Pin = 25;

/* I\O PIN MAPPING AD9850 MODULE 1- Pulse Frequency Generator */
const int DDS1_CLK_Pin = 26;
const int DDS1_FQ_Pin = 27;
const int DDS1_DATA_Pin = 28;
const int DDS1_RESET_Pin = 29;

/* CREATE AD9850 CLASS INSTANCES */
AD9850 DDS_Gate(DDS0_CLK_Pin, DDS0_FQ_Pin, DDS0_DATA_Pin); // w_clk, fq_ud, Sdata
AD9850 DDS_Pulse(DDS1_CLK_Pin, DDS1_FQ_Pin, DDS1_DATA_Pin); // w_clk, fq_ud, Sdata
//---------------------------------------------

/* I\O PIN MAPPING BUZZER MODULE  */
//const uint8_t Buzzer_Pin = 30;
//const unsigned int BuzzerToneFq = NOTE_C4;
//const unsigned long BuzzerShortTone = 500;
//const unsigned long BuzzerLongTone = 1000;

/* CREATE BUZZER CLASS INSTANCE */
//Tone buzzer[1];
//buzzer[0].begin(Buzzer_Pin);


/* Define Locale Variables */
int FuncKey = 0;
String keyString = "";
int F_Scan_min = 500;                                                //Low end of freqency fine tune scale
int F_Scan_max = 5000;                                               //High end of freqency fine tune scale
int F_Resonace = 4243;                                                  //Variable for Locked frequency
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


/* Main Program Initial Setup */
void setup() 
{ 
  //lcd.createChar(0, lock);
  //lcd.createChar(1, watermol);
  //H2OtoHHO::LoadSymbols();
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(CUSTOM_WATER_MOLECULE);
  lcd.print(" H20 to HHO ");
  lcd.setCursor(0, 1);
  lcd.print("Generator v1.0 ");
  lcd.write(CUSTOM_LOCK);
  delay(2500);
  
  /*
  OPTIONAL
  keypad.setRate(x);
  Sets the sample rate at once every x milliseconds.
  Default: 10ms
  */
  keypad.setRate(10);
  
  UpdateKeypress(FuncKey);
  
  F_Resonace = ResonanceScan();
}
//---------------------------------------------


/* Main Program Loop */
void loop()
{
  int i=0, k=0;
  
  FuncKey = lcd.button();
   
  switch (FuncKey) 
  {
    case KEYPAD_RIGHT:
        UpdateKeypress(FuncKey);
      break;
      
    case KEYPAD_UP:
        UpdateKeypress(FuncKey);
      break;
      
    case KEYPAD_DOWN:
        UpdateKeypress(FuncKey);
      break;
      
    case KEYPAD_LEFT:
        UpdateKeypress(FuncKey);
      break;
      
    case KEYPAD_SELECT:
        lcd.begin(16, 2);
        lcd.clear();
        lcd.print("     MAIN");
        lcd.setCursor(0,1);
        lcd.print("     MENU");
        delay(3000);
        
        for (k=0;k<16;k++)
        {
          lcd.scrollDisplayLeft();
          delay(200);
        }
        
        MainMenu();
        
      break;
      
    default:
      if (FuncKey != KEYPAD_NONE)
      {
        UpdateKeypress(FuncKey);
      }
   }    
}
//---------------------------------------------








