/*
  H2OtoHHO.h
*/

// ensure this library description is only included once
#ifndef H2OtoHHO_h
#define H2OtoHHO_h

// library interface description
#define CURSOR_RIGHT 0
#define CURSOR_UP 1
#define CURSOR_DOWN 2
#define CURSOR_LEFT 3
#define CURSOR_SELECT 4
#define CUSTOM_LOCK 5
#define CUSTOM_WATER_MOLECULE 6


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


/*
LoadSymbols()
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


class H2OtoHHO: public LCDKeypad
{
  public:
    H2OtoHHO(LCDKeypad &disp){
		disp.createChar(CURSOR_RIGHT, c_right);
		disp.createChar(CURSOR_UP, c_up);
		disp.createChar(CURSOR_DOWN, c_down);
		disp.createChar(CURSOR_LEFT, c_left);
		disp.createChar(CURSOR_SELECT, c_select);
		disp.createChar(CUSTOM_LOCK, custom_lock);
		disp.createChar(CUSTOM_WATER_MOLECULE, custom_watermol);
	};
};


#endif
