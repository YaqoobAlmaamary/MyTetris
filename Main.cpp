#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GameStateManager.h"

GameStateManager bigBoss = GameStateManager();

void display()
{
	bigBoss.current = std::chrono::system_clock::now(); // get the current time
	bigBoss.display();
	
}

void keyboard( unsigned char key, int x, int y )
{
	if ( bigBoss.state == 2 )
		bigBoss.inputManager.logKey( key );
}

void idle()
{
	if ( bigBoss.state == 2 ) // gameplay state (the game started)
	{
		glutSetCursor( GLUT_CURSOR_NONE );
		glutWarpPointer( bigBoss.engine.windowWidth / 2, bigBoss.engine.windowHeight / 2 );
		bigBoss.playGame();
	}
	if ( bigBoss.state == 3 ) // game over menu
	{
		glutSetCursor( GLUT_CURSOR_LEFT_ARROW );
	}
	if ( bigBoss.state == 4 )
	{
		glutExit();
		exit( 0 );
	}
	
}

void mouse( int button, int state, int x, int y )
{
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		bigBoss.processMenu( x, y );
	}
}

int main()
{
	bigBoss.InitGlut();

	// call back functions
	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutIdleFunc( idle );
	glutMouseFunc( mouse );

	// load and compile shaders
	bigBoss.startEngine();
	bigBoss.generateShape();
	// log time before starting the infinite loop
	bigBoss.glTimeStamp = std::chrono::system_clock::now();
	// start the infinite loop
	bigBoss.run();

	return 0;
}
