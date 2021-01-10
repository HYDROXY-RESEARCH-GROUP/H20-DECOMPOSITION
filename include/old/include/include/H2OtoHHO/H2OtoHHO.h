/*
  H2OtoHHO.h
*/

// ensure this library description is only included once
#ifndef H2OtoHHO_h
#define H2OtoHHO_h

#define FREQ_MIN 1                                                //Low end of freqency fine tune scale
#define FREQ_MAX 1000                                             //High end of freqency fine tune scale
#define SCAN_FREQ_MIN 500                                         //Low end of freqency auto tune scale
#define SCAN_FREQ_MAX 5000                                        //High end of freqency auto tune scale


// library interface description
#define CURSOR_SELECT 0
#define CURSOR_LEFT 1
#define CURSOR_UP 2
#define CURSOR_DOWN 3
#define CURSOR_RIGHT 4
#define CUSTOM_WATER_MOLECULE 5
#define CUSTOM_LOCK 6

/* I\O PIN MAPPING AD9850 MODULE 0- Gate Frequency Generator  */
#define DDS0_CLK_Pin 22
#define DDS0_FQ_Pin 23
#define DDS0_DATA_Pin 24
#define DDS0_RESET_Pin 25

/* I\O PIN MAPPING AD9850 MODULE 1- Pulse Frequency Generator */
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


class LCDKeypad;
class DFR_Key;
class AD9850;


//class H2OtoHHO: public LCDKeypad, public AD9850
class H2OtoHHO
{
  public:
    H2OtoHHO();
    int ResonanceScan();
    int MainMenu();
    int UpdateKeypress(int keypress);
    //int getFuncKey();
    
  private:
    //static display
    LCDKeypad *screen;
    DFR_Key *ctrls;
    AD9850 *gate, *pulse;    
};

#endif
