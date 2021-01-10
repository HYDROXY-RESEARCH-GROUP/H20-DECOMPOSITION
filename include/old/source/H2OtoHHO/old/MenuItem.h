/*
  MenuItem.h
*/

// ensure this library description is only included once
#ifndef MenuItem_h
#define MenuItem_h


// include Standard library header files
//#include <array>

// library constant description

// library interface description


class MenuItem 
{
	public:
		MenuItem( int item_id, int parent_id );
		virtual int SetItemName( String name );
		
	private:
		int itemID, parentID;
		String itemName;
};

// include this library's description files
//#include "MenuItem.cpp"

#endif

