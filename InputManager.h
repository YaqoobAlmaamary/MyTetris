#pragma once
#include "Gameboard.h"

class InputManager
{
	
public:
	bool key[5];
	void doMovement( Gameboard* board );
	void logKey( unsigned int key );
	void unlogKeys();
	void unlogKey( unsigned int key );
private:
	enum button{ w, s, a, d };
};

