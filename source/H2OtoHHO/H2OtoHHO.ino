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


//Pin assignments for SainSmart LCD Keypad Shield
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 



#include "H2OtoHHO.h"





H2OtoHHO gen;
//H2OtoHHO loadSymbols(lcd);
//---------------------------------------------



/* Main Program Initial Setup */
void setup() 
{ 
   
  // Startup Splash Screen
  gen.begin(16, 2);
  gen.clear();
  gen.setCursor(0, 0);
  gen.write(CUSTOM_WATER_MOLECULE);
  gen.print(" H20 to HHO ");
  gen.write(CUSTOM_WATER_MOLECULE2);
  gen.setCursor(0, 1);
  gen.print("Generator v1.0 ");
  
  
  delay(2500);
  
  /*
  OPTIONAL
  keypad.setRate(x);
  Sets the sample rate at once every x milliseconds.
  Default: 10ms
  */
  gen.setRate(10);
  
  //gen.UpdateKeypress(gen.FuncKey);
  
  //gen.ResonanceScan();
}
//---------------------------------------------


/* Main Program Loop */
void loop()
{
  int i=0, k=0, func_key=-1;
  
  
  func_key = gen.button();
  
  Serial.write(func_key);

  //gen.MainMenu();
  
  

   delay(250);
}
//---------------------------------------------








