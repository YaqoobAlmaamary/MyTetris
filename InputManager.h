#pragma once
#include "Gameboard.h"
#include "Menu.h"

class InputManager
{
	
public:
	// variables
	bool key[5];
	
	// methods
	void doMovement( Gameboard* board );
	void logKey( unsigned int key );
	void unlogKeys();
	void unlogKey( unsigned int key );
	int processMenu( float x, float y, Menu menu );

private:
	// enumneration
	enum button{ w, s, a, d };



};

