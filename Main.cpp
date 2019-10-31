#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GameStateManager.h"
#include <chrono>

GameStateManager bigBoss = GameStateManager();
std::chrono::system_clock::time_point end;
std::chrono::system_clock::time_point current;
std::chrono::system_clock::time_point glTimeStamp; // game loop time stamp
std::chrono::system_clock::time_point sdTimeStamp; // shift dowm time stamp
std::chrono::duration<float> glDuration; // duration for the game loop
std::chrono::duration<float> sdDuration; // duration for the shift down statment
bool flag = true;

void display()
{
	current = std::chrono::system_clock::now(); // get the current time
	bigBoss.display(); // draw blocks
	
}

void keyboard( unsigned char key, int x, int y )
{
	bigBoss.inputManager.logKey( key );
}

void idle()
{
	end = std::chrono::system_clock::now();// get current time
	glDuration = end - glTimeStamp; // calculate time taken for block drawing
	sdDuration = end - sdTimeStamp;
	
	if ( glDuration.count() >= 1.0 / 60 && flag )// did the frame took 1/60 of a second
	{
		// if yes do game logic
		glTimeStamp = current;
		// start for game logic discussed in Game flow logic diagram

		// check right boundary
		if ( bigBoss.rightBoundary() )
		{
			bigBoss.inputManager.unlogKey( 'd' );
			bigBoss.inputManager.unlogKey( 'w' );
		}

		// check left boundary
		if ( bigBoss.leftBoundary() )
		{
			bigBoss.inputManager.unlogKey( 'a' );
			bigBoss.inputManager.unlogKey( 'w' );
		}

		// do Movement
		bigBoss.doMovement();
		// unlog all keys
		bigBoss.inputManager.unlogKeys();

		// check if one second has passed
		if ( sdDuration.count() >= 1.0 / 1 )
		{
			// check bottom boundary
			if ( bigBoss.bottomBoundary() )
			{
				bigBoss.placeShape();

				//delete filled rows
				if ( bigBoss.deleteFilledRows() )
				{
					// shift all blocks down when a row is deleted
					bigBoss.shiftBlocksDown();
				}
				bigBoss.generateShape();

				// check if game over
				if ( bigBoss.isEndGame() )
				{
					printf( "Game over son" );
					flag = false;
				}
			}
			else
			{
				(bigBoss.board.getCurrentShape())->shiftDown();
			}
			sdTimeStamp = current;
		}
	}
	// redraw 
	glutPostRedisplay();
}

int main()
{
	bigBoss.InitGlut();

	// call back functions
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutIdleFunc( idle );

	// load and compile shaders
	bigBoss.startEngine();
	bigBoss.generateShape();
	glTimeStamp = std::chrono::system_clock::now();
	bigBoss.run();

	return 0;
}
