/*
  LCDKeypad.cpp
*/

// include this library's header file
#include "LCDKeypad/LCDKeypad.h"

//#include "WProgram.h"
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

int LCDKeypad::NUM_KEYS = KEYPAD_BUTTON_COUNT;
int LCDKeypad::adc_key_val[KEYPAD_BUTTON_COUNT] = {KEY_VALUE_RIGHT,
                                                 KEY_VALUE_UP,
                                                 KEY_VALUE_DOWN,
                                                 KEY_VALUE_LEFT,
                                                 KEY_VALUE_SELECT};

LCDKeypad::LCDKeypad() 
  : LiquidCrystal(LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D0, LCD_PIN_D1, LCD_PIN_D2, LCD_PIN_D3)
{
}

int LCDKeypad::button()
{
  int k, input;
  
  input=analogRead(0);
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
      return k;
    }
  }
  if (k >= NUM_KEYS)
    k = -1;     // No valid key pressed
  return k;
}