/*
  LCDKeypad.h
*/

#include <LiquidCrystal.h>
  //class LiquidCrystal;

// library Constant Definitions
#define KEYPAD_BUTTON_COUNT 5


// library interface description
#define KEYPAD_NONE -1
#define KEYPAD_RIGHT 0
#define KEYPAD_UP 1
#define KEYPAD_DOWN 2
#define KEYPAD_LEFT 3
#define KEYPAD_SELECT 4

// library interface description
#define KEY_VALUE_NONE 0
#define KEY_VALUE_RIGHT 30
#define KEY_VALUE_UP 230
#define KEY_VALUE_DOWN 535
#define KEY_VALUE_LEFT 760
#define KEY_VALUE_SELECT 1023

// library IO Pin Definitions
#define LCD_PIN_RS 8
#define LCD_PIN_ENABLE 9
#define LCD_PIN_D0 4
#define LCD_PIN_D1 5
#define LCD_PIN_D2 6
#define LCD_PIN_D3 7


// ensure this library description is only included once
#ifndef LCDKeypad_h
  #define LCDKeypad_h

class LCDKeypad : public LiquidCrystal
{
  public:
    LCDKeypad();
    int button();

  private:
    static int NUM_KEYS;
    static int adc_key_val[KEYPAD_BUTTON_COUNT];
};

#endif

