/*
  setLocale.h
*/
/*************************************************
 *	Locale Settins File
 *************************************************/

// ensure this library description is only included once
#ifndef SetLocale_h
	#define SetLocale_h

	/* Locale Settings */
	#define LOCALE_DIR_PATH NULL
	#define LOCALE_DEFAULT EN_JM
	#define SET_LOCALE EN_JM
	
	
	/* Global Settings */
	#define TOTAL_MENU_COUNT 4
	#define ROOT_MENU_ID 0


	/* Main Menu */
	#define MENU0_ID 0
	#define MENU0_ITEMS_COUNT 4
	#define MENU0_ITEM_DEFAULT 1


	/* Sub Menu-1 */
	#define MENU1_ID 1
	#define MENU1_ITEMS_COUNT 4
	#define MENU1_ITEM_DEFAULT 1


	/* Sub Menu-2 */
	#define MENU2_ID 1
	#define MENU2_ITEMS_COUNT 4
	#define MENU2_ITEM_DEFAULT 1


	/* Sub Menu-3 */
	#define MENU3_ID 1
	#define MENU3_ITEMS_COUNT 4
	#define MENU3_ITEM_DEFAULT 1


	/* Sub Menu-4 */
	#define MENU4_ID 1
	#define MENU4_ITEMS_COUNT 4
	#define MENU4_ITEM_DEFAULT 1


	#if defined(LOCALE_DIR_PATH) && defined(SET_LOCALE)
		#if LOCALE_DIR_PATH != NULL && SET_LOCALE != NULL
			#include (LOCALE_DIR_PATH & "\" & "locale_" & SET_LOCALE & ".h")
		#elseif LOCALE_DIR_PATH != NULL && SET_LOCALE == NULL 
			#include (LOCALE_DIR_PATH & "\" & "locale_" & LOCALE_DEFAULT & ".h")
		#elseif	LOCALE_DIR_PATH == NULL && SET_LOCALE != NULL
			#include ("locale_" & SET_LOCALE & ".h")
		#elseif	LOCALE_DIR_PATH == NULL && SET_LOCALE == NULL
			#include ("locale_" & LOCALE_DEFAULT & ".h")
		#endif
	#else
		#include ("locale_" & LOCALE_DEFAULT & ".h")
	#endif
	
	
	
	//#include "setlocale.cpp"

#endif






