#pragma once
#include "RenderEngine.h"
#include "InputManager.h"
#include "Gameboard.h"
#include "Leaderboard.h"
#include <chrono>

class GameStateManager
{
public:
	// variables
	RenderEngine engine;
	InputManager inputManager;
	Gameboard board = Gameboard( 10, 20 );
	Leaderboard leaderboard;

	/* refers to the states in which the game is 
	*  state = 0 means main menu
	*  state = 1 means option menu
	*  state = 2 means play game
	*  state = 3 means gameOver
	*  state = 4 means quit
	*/
	int state = 0;

	// newly added
	std::chrono::system_clock::time_point end;
	std::chrono::system_clock::time_point current;
	std::chrono::system_clock::time_point glTimeStamp; // game loop time stamp
	std::chrono::system_clock::time_point sdTimeStamp; // shift dowm time stamp
	std::chrono::duration<float> glDuration; // duration for the game loop
	std::chrono::duration<float> sdDuration; // duration for the shift down statment

	bool flag = true;
	int frames = 0;
	int speed = 1;

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

	// newly added
	void playGame();
	void displayMainMenu();
	void displayOptionMenu();
	void displayGameOver();
	void processMenu( int x, int y );

};

