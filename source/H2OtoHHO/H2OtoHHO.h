/*
  H2OtoHHO.h
*/

// ensure this library description is only included once
#ifndef H2OtoHHO_h
#define H2OtoHHO_h


// include Standard library header files
//#include <queue>
#include <map>
#include <LiquidCrystal.h>
#include <Tone.h>
#include <LCDKeypad.h>
#include <DFR_Key.h>
#include <AD9850.h>


// include program library header files
#include "setLocale.h"
#include "pitches.h"
//#include "MenuItem.h"
//#include "include\LCDKeypad\LCDKeypad.h"
//#include "include\DFR_Key\DFR_Key.h"
//#include "include\AD9850\AD9850.h"

// include program library description files
//#include "include\LCDKeypad\LCDKeypad.cpp"
//#include "include\DFR_Key\DFR_Key.cpp"
//#include "include\AD9850\AD9850.cpp"


/* I\O PIN MAPPING AD9850 MODULE 0- Gate Frequency Generator  */
#define PDO_DDS0_CLK 22
#define PDO_DDS0_FREQ 23
#define PDO_DDS0_DATA 24
#define PDO_DDS0_RESET 25

/* I\O PIN MAPPING AD9850 MODULE 1- Pulse Frequency Generator */
#define PDO_DDS1_CLK 26
#define PDO_DDS1_FREQ 27
#define PDO_DDS1_DATA 28
#define PDO_DDS1_RESET 29

/* I\O PIN MAPPING BUZZER MODULE  */
//const uint8_t Buzzer_Pin = 30;
//const unsigned int BuzzerToneFq = NOTE_C4;
//const unsigned long BuzzerShortTone = 500;
//const unsigned long BuzzerLongTone = 1000;


#define FREQ_MIN 1                                                //Low end of freqency fine tune scale
#define FREQ_MAX 1000                                             //High end of freqency fine tune scale
#define SCAN_FREQ_MIN 500                                         //Low end of freqency auto tune scale
#define SCAN_FREQ_MAX 5000                                        //High end of freqency auto tune scale
//#define KEYPRESS_BUFF_LEN 5									  // Maximum Keypress History



/* CREATE BUZZER CLASS INSTANCE */
//Tone buzzer[1];
//buzzer[0].begin(Buzzer_Pin);


/* Define local constant definitions  */
//#define EXEC_SUCCESS 0
//#define EXEC_FAILED -1
enum ExecStatus { EXEC_FAILED=-1, EXEC_SUCCESS=0 };

// library interface description
/*
#define CURSOR_SELECT 0
#define CURSOR_LEFT 1
#define CURSOR_UP 2
#define CURSOR_DOWN 3
#define CURSOR_RIGHT 4
#define CUSTOM_LOCK 5
#define CUSTOM_WATER_MOLECULE 6
#define CUSTOM_WATER_MOLECULE2 7
*/
enum CustomLCDIcons {
	CURSOR_SELECT,
	CURSOR_LEFT,
	CURSOR_UP,
	CURSOR_DOWN,
	CURSOR_RIGHT,
	CUSTOM_LOCK,
	CUSTOM_WATER_MOLECULE,
	CUSTOM_WATER_MOLECULE2
};


//class LCDKeypad;
//class DFR_Key;
//class AD9850;




class H2OtoHHO: public LCDKeypad, public DFR_Key
{
  public:
    H2OtoHHO();
    enum SupportedLocale { EN_US, EN_JM };
    virtual ExecStatus LoadLocale( String locale );
  	virtual ExecStatus UpdateMenu( int menu_id );
    //static ExecStatus ResonanceScan();
    //static ExecStatus UpdateKeypress(int keypress);
    virtual int getKeyPress();
  	const AD9850 gate, pulse;
    typedef std::map<int, String> SubMenuList;
    struct MenuItem
    {
      String itemName;
      SubMenuList *SubMenu; 
    };
    std::map<int, String> MainMenuList;
    //MenuItem menuList;	
    
  private:
    int keyPress_cur = -1;
  	//, keyPress_buffer[KEYPRESS_BUFF_LEN];
  	
};

// include this library's description files
//#include "H2OtoHHO.cpp"

#endif
