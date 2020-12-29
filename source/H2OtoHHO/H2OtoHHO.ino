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
#include <H2OtoHHO.h>


//Pin assignments for SainSmart LCD Keypad Shield
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
//#define MINVAL 1
//#define MAXVAL 1000

H2OtoHHO gen;
//H2OtoHHO loadSymbols(lcd);
//---------------------------------------------



/* Main Program Initial Setup */
void setup() 
{ 
  //lcd.createChar(0, lock);
  //lcd.createChar(1, watermol);
  //H2OtoHHO::LoadSymbols();
  
  gen.screen->begin(16, 2);
  gen.screen->clear();
  gen.screen->setCursor(0, 0);
  gen.screen->print(" H20 to HHO ");
  gen.screen->setCursor(0, 1);
  gen.screen->print("Generator v1.0 ");
  gen.screen->write(CUSTOM_LOCK);
  delay(2500);
  
  /*
  OPTIONAL
  keypad.setRate(x);
  Sets the sample rate at once every x milliseconds.
  Default: 10ms
  */
  gen->ctrls.setRate(10);
  
  //gen.UpdateKeypress(gen.FuncKey);
  
  gen.ResonanceScan();
}
//---------------------------------------------


/* Main Program Loop */
void loop()
{
  int i=0, k=0, func_key=0;
  
  
  func_key = gen.screen->button();
   
  switch (func_key) 
  {
    case KEYPAD_RIGHT:
        gen.UpdateKeypress(func_key);
      break;
      
    case KEYPAD_UP:
        gen.UpdateKeypress(func_key);
      break;
      
    case KEYPAD_DOWN:
        gen.UpdateKeypress(func_key);
      break;
      
    case KEYPAD_LEFT:
        gen.UpdateKeypress(func_key);
      break;
      
    case KEYPAD_SELECT:
        gen.screen->begin(16, 2);
        gen.screen->clear();
        gen.screen->print("     MAIN");
        gen.screen->setCursor(0,1);
        gen.screen->print("     MENU");
        delay(3000);
        
        for (k=0; k<16; k++)
        {
          gen.screen->scrollDisplayLeft();
          delay(200);
        }
        
        gen.MainMenu();
        
      break;
      
    default:
      if (func_key != KEYPAD_NONE)
      {
        gen.UpdateKeypress(func_key);
      }
   }    
}
//---------------------------------------------








