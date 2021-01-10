/*
  MenuItem.cpp
*/

//#include "WProgram.h"
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
  #else
	#include "WProgram.h"
#endif


// include this library's description file
#include "MenuItem.h"

MenuItem::MenuItem( int item_id, int parent_id )
{
	this->itemID = item_id;
	this->parentID = parent_id;
}

int MenuItem::SetItemName( String name )
{
	this->itemName = name;
	
	return 0;
}


