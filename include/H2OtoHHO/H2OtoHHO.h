/*
  H2OtoHHO.h
*/

// library interface constant definitions
#define CUSTOM_CHARACTER_BYTES 8

// library interface description
#define SCAN_FREQ_MIN 1            //Low end of triggerpulseency fine tune scale
#define SCAN_FREQ_MAX 1000         //High end of triggerpulseency fine tune scale
#define SCAN_TRIGGERPULSE_MIN 500  //Low end of triggerpulseency auto tune scale
#define SCAN_TRIGGERPULSE_MAX 5000 //High end of triggerpulseency auto tune scale

#define CURSOR_SELECT 0
#define CURSOR_LEFT 1
#define CURSOR_UP 2
#define CURSOR_DOWN 3
#define CURSOR_RIGHT 4
#define CUSTOM_WATER_MOLECULE 5
#define CUSTOM_LOCK 6

#define DISPLAY_LINES_ROWS 2
#define DISPLAY_LINES_COLUMNS 16

#define CONFIG_FILE "config.xml"
#define CONFIG_LOCALE "JM-EN"
//#define UNIT_MERTIC_PREFIX {'G','M','K',' ','m','u','p'}
#define UNIT_MERTIC_PREFIX "GMK mup"

#define MAIN_MENU_ITEMS_COUNT 4
#define MAIN_MENU_ITEM0 " 1. Exit Menu!"
#define MAIN_MENU_ITEM1 " 2. Re-Scan TriggerPulse."
#define MAIN_MENU_ITEM2 " 3. [Option #2]"
#define MAIN_MENU_ITEM3 " 4. Debug Mode"

#define HOMESCREEN_OBJ_COUNT 4
#define MAIN_MENU_ITEM0 " 1. Exit Menu!"
#define MAIN_MENU_ITEM1 " 2. Re-Scan TriggerPulse."
#define MAIN_MENU_ITEM2 " 3. [Option #2]"
#define MAIN_MENU_ITEM3 " 4. Debug Mode"

/* I\O PIN MAPPING AD9850 MODULE 0- TriggerRamp TriggerPulseuency Generator  */
#define DDS0_CLK_Pin 22
#define DDS0_FQ_Pin 23
#define DDS0_DATA_Pin 24
#define DDS0_RESET_Pin 25

/* I\O PIN MAPPING AD9850 MODULE 1- Pulse TriggerPulseuency Generator */
#define DDS1_CLK_Pin 26
#define DDS1_FQ_Pin 27
#define DDS1_DATA_Pin 28
#define DDS1_RESET_Pin 29

/* I\O PIN MAPPING BUZZER MODULE  */
//const uint8_t Buzzer_Pin = 30;
//const unsigned int BuzzerToneFq = NOTE_C4;
//const unsigned long BuzzerShortTone = 500;
//const unsigned long BuzzerLongTone = 1000;

/* CREATE BUZZER CLASS INSTANCE */
//Tone buzzer[1];
//buzzer[0].begin(Buzzer_Pin);

// ensure this library description is only included once
#ifndef H2OtoHHO_h
#define H2OtoHHO_h

#include "etl/string.h"
//#include "etl/basic_string_stream.h"
//#include <iomanip>
//#include <string>
#include "xmlParser/xmlParser.h"

#include "LCDKeypad/LCDKeypad.h"
#include "LCDKeypad/LCDKeypad.cpp"
#include "DFR_Key/DFR_Key.h"
#include "DFR_Key/DFR_Key.cpp"
#include "AD9850/AD9850.h"
#include "AD9850/AD9850.cpp"

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <stdio.h>  // to get "printf" function
#include <stdlib.h> // to get "free" function
#include <math.h>

//using namespace std;
using namespace etl;

template <typename T>
class Attribute
{
protected:
  T m_val;

public:
  T *getAddress() { return &m_val; }
  T get() { return m_val; }
  void set(T v) { m_val = v; }
};

class H2OtoHHO
{
private:
  Attribute<double> _trigger_ramp_freq;
  Attribute<double> _trigger_pulse_freq;
  Attribute<double> _trigger_ramp_duty;
  Attribute<double> _trigger_resonance_voltge;
  string<DISPLAY_LINES_ROWS> _display_chars[DISPLAY_LINES_COLUMNS];

protected:
  static byte _c_right[];
  static byte _c_up[];
  static byte _c_down[];
  static byte _c_left[];
  static byte _c_select[];
  static byte _custom_lock[];
  static byte _custom_watermol[];
  static String _mainMenuItems[];

public:
  H2OtoHHO();
  int ResonanceScan();
  int HomeScreen();
  int MainMenu();
  int UpdateKeypress(int keypress);

  //double getTriggerRampValue();
  //double getTriggerPulseValue();
  int getConfigData(String cfgfile = CONFIG_FILE, String locale = CONFIG_LOCALE);
  char getUnitPrefix(double val);

  LCDKeypad screen;
  DFR_Key ctrls;
  class DSS_Synthesizer : public AD9850
  {
    private:

    public:
      void PowerDown

  } TriggerRamp, TriggerPulse;


};

#endif