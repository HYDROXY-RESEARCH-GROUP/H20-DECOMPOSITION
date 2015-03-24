/*
  H2OtoHHO.cpp
*/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// include this library's description file
//#include <LiquidCrystal.h>
//#include <Tone.h>
#include "pitches.h"
#include "D:\Users\Ryan\GitHub\H20-DECOMPOSITION\source\R1.0\H2OtoHHO\include\LCDKeypad\LCDKeypad.h"
#include "D:\Users\Ryan\GitHub\H20-DECOMPOSITION\source\R1.0\H2OtoHHO\include\DFR_Key\DFR_Key.h"
#include "D:\Users\Ryan\GitHub\H20-DECOMPOSITION\source\R1.0\H2OtoHHO\include\AD9850\AD9850.h"
#include "H2OtoHHO.h"
//#include <H2OtoHHO.h>
// ensure this library description is only included once


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
	B0000
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


H2OtoHHO::H2OtoHHO() : public LCDKeypad()
{
    this->createChar(CURSOR_SELECT, c_select);
    this->createChar(CURSOR_LEFT, c_left);
    this->createChar(CURSOR_UP, c_up);
    this->createChar(CURSOR_DOWN, c_down);
    this->createChar(CURSOR_RIGHT, c_right);
    this->createChar(CUSTOM_WATER_MOLECULE, custom_watermol);
    this->createChar(CUSTOM_LOCK, custom_lock);    
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
  
  lcd.clear();
  lcd.print("  SCANNING RANGE....  ");
   
  // Sweep frequency from 'F_Scan_min' to 'F_Scan_max' 
  for (uint32_t i = F_Scan_min; i < F_Scan_max; i++)
  {        
    lcd.setCursor(3,1);
    lcd.print(i);
    lcd.print(" Hz  ");
    
    DDS_Gate.setfreq(i);
    DDS_Pulse.setfreq(i*10);
  }
  
  delay(200);
  lockFreq = F_Resonace;
  lcd.print(" ");
  lcd.write(CUSTOM_LOCK);
  lcd.print(" ");
  lcd.print( lockFreq );
  lcd.print(" Hz  ");  
  delay(2000);
  
  return lockFreq;
}
//---------------------------------------------



/* Main Menu Function  */
int H2OtoHHO::MainMenu ()
{
  int k = 0, exitCode = -1, SelectedItem = 0, keypress= 0;
  String MainItems[4] = {
    " 1. Exit Menu!",
    " 2. Re-Scan Freq.",
    " 3. [Option #2]",
    " 4. Debug Mode" };
    
  
  do
  {
    //keypress = lcd.button();
    
    switch ( lcd.button() ) 
    {
      //case KEYPAD_RIGHT:
      //  break;
        
      case KEYPAD_UP:
          if ( SelectedItem > 0 )
          {
            SelectedItem--;
            lcd.setCursor(0,1);
            lcd.print( MainItems[SelectedItem] );
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
            lcd.setCursor(0,1);
            lcd.print( MainItems[SelectedItem] );
            delay(2000);
          }
          //else
            //buzzer.play( NOTE_C4, BuzzerShortTone );
            
             //exitCode = 0;
        break;
        
      //case KEYPAD_LEFT:
      //  break;
        
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
        exitCode = 0;
    }
    
  } while (exitCode!=-1);
  
  return exitCode;  
}
//---------------------------------------------


/* Updates Display upon Keypress */
int H2OtoHHO::UpdateKeypress(int keypress)
{
  //if (keypress != KEYPAD_NONE)
  //{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Current Key:");
    lcd.setCursor(0, 1);
    lcd.print(FuncKey);
    lcd.print(" => ");
    lcd.print(analogRead(0));
    lcd.print(", ");
    lcd.print(lcd.button());
    delay(1000);
  //}
  return 0;
}
//---------------------------------------------


