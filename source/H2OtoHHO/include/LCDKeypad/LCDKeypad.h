/*
  LCDKeypad.h
*/

// ensure this library description is only included once
#ifndef LCDKeypad_h
#define LCDKeypad_h

//#include <LiquidCrystal.h>
class LiquidCrystal;


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


class LCDKeypad: public LiquidCrystal
{
  public:
    LCDKeypad();
    int button();
};

#endif

