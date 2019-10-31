#include "InputManager.h"

void InputManager::doMovement( Gameboard* board )
{
	Shapes* currentShape = board->getCurrentShape();
	if ( key[w] )
		currentShape->rotateCounterClockWise();
	if ( key[a] )
		currentShape->shiftLeft();
	if ( key[d] )
		currentShape->shiftRight();
	if ( key[s] )
		;
	
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