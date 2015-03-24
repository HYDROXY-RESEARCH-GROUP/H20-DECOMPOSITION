/*
  H2OtoHHO.h
*/

// ensure this library description is only included once
#ifndef H2OtoHHO_h
#define H2OtoHHO_h

#define MINVAL 1
#define MAXVAL 1000


// library interface description
#define CURSOR_SELECT 0
#define CURSOR_LEFT 1
#define CURSOR_UP 2
#define CURSOR_DOWN 3
#define CURSOR_RIGHT 
#define CUSTOM_WATER_MOLECULE 5
#define CUSTOM_LOCK 6


class H2OtoHHO: public LCDKeypad
{
  public:
    H2OtoHHO();
    
  private:
    
};

#endif
