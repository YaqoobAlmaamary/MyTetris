#include "InputManager.h"

void InputManager::doMovement( Gameboard* board )
{
	if ( key[w] )
		board->rotateCounterClockWise();
	if ( key[a] )
		board->shiftShapeLeft();
	if ( key[d] )
		board->shiftShapeRight();
	if ( key[s] )
		board->pushShapeDown();
	
}

void InputManager::logKey( unsigned int key )
{
	switch ( key )
	{
	case 'w':
		this->key[w] = true;
		break;
	case 's':
		this->key[s] = true;
		break;
	case 'd':
		this->key[d] = true;
		break;
	case 'a':
		this->key[a] = true;

	}
}

void InputManager::unlogKeys()
{
	for ( int i = 0; i < 4; i++ )
		key[i] = false;
}

void InputManager::unlogKey( unsigned int key )
{
	switch ( key )
	{
	case 'w':
		this->key[w] = false;
		break;
	case 's':
		this->key[s] = false;
		break;
	case 'd':
		this->key[d] = false;
		break;
	case 'a':
		this->key[a] = false;

	}
}

int InputManager::processMenu( float x, float y, Menu menu )
{
	// iterate through the buttons and check if the click occured 
	// inside the boundaries of a button in world coordinates, if true return the index
	// of the clicked button

	for ( int i = 0; i < menu.buttons.size(); i++ )
	{
		if( x > menu.buttons[i].x && x < menu.buttons[i].x + menu.buttons[i].width )
			if ( y < menu.buttons[i].y && y > menu.buttons[i].y - menu.buttons[i].height )
			{
				printf( "True\n" );
				return i;
			}
	}
	return -1;
}

