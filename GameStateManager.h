#pragma once
#include "RenderEngine.h"
#include "InputManager.h"
#include "Gameboard.h"
class GameStateManager
{
public:
	// variables
	RenderEngine engine;
	InputManager inputManager;
	Gameboard board = Gameboard( 10, 10 );
	int state;

	// methods
	void InitGlut();
	void display();
	void keyPress( unsigned char key, int x, int y );
	void run();
	void startEngine();
	bool leftBoundary(); // returns true if current shape has a block near if or is near left boundary
	bool rightBoundary(); // returns true if current shape has a block near if or is near right boundary
	bool bottomBoundary(); // returns true if current shape has a block near if or is near bottom boundary
	void doMovement();
	void generateShape();
	void placeShape();
	bool deleteFilledRows(); // checks if a row is filled
	void shiftBlocksDown(); // shifts blocks down
	bool isEndGame(); // check if current shape overlaps a block

};

