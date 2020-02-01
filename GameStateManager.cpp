#include "GameStateManager.h"

void GameStateManager::display()
{
	if ( state == 0 )
		 displayMainMenu();
	if ( state == 1 )
		 displayOptionMenu();
	if ( state == 2 )
		engine.render( &board );
	if ( state == 3 )
		 displayGameOver();
}

void GameStateManager::keyPress( unsigned char key, int x, int y )
{
	inputManager.logKey( key );
}

void GameStateManager::InitGlut()
{
	// initalize glut for window events
	int a = 0;
	char b = 'a';
	char* pb = &b;
	char** ppb = &pb;
	glutInit( &a, ppb );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowSize( engine.windowWidth, engine.windowHeight );
	glutInitWindowPosition( 0, 0 );
	glutInitContextVersion( 4, 3 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutCreateWindow( "tetris" );
	
	// initalize glew
	if ( glewInit() )
	{
		std::printf( "glew Error\n" );
		exit( EXIT_FAILURE );
	}

	// set Opengl States
	glEnable( GL_DEPTH_TEST );
}

void GameStateManager::run()
{
	glutMainLoop();
}

void GameStateManager::startEngine()
{
	engine.initData();
	engine.initMenus( board.getColumns() * 0.1, board.getRows() * 0.1 );
}

bool GameStateManager::leftBoundary()
{
	Shapes* currentShape = board.getCurrentShape();
	bool** cells = board.getCells();
	// check if any of the blocks column location is 0 (checking left boundary)
	for ( int i = 0; i < 4; i++ )
	{
		if ( currentShape->blockLocationColumn[i] == 0 )
		{
			return true;
		}
	}

	// check if a block is next to the current shape from the left
	for ( int i = 0; i < 4; i++ )
	{
		if ( cells[currentShape->blockLocationColumn[i] - 1][currentShape->blockLocationRow[i]] == 1 )
		{
			return true;
		}
	}

	return false;
}

bool GameStateManager::rightBoundary()
{
	Shapes* currentShape = board.getCurrentShape();
	bool** cells = board.getCells();
	// check if any of the blocks column location is number of columns - 1 (checking right boundary)
	for ( int i = 0; i < 4; i++ )
	{
		if ( currentShape->blockLocationColumn[i] == board.getColumns() - 1 )
		{ 
			return true;
		}
	}
	// check if a block is next to the current shape from the right
	for ( int i = 0; i < 4; i++ )
	{
		if ( cells[currentShape->blockLocationColumn[i] + 1][currentShape->blockLocationRow[i]] == 1 )
		{
			return true;
		}
	}
	return false;
}

bool GameStateManager::bottomBoundary()
{
	Shapes* currentShape = board.getCurrentShape();
	bool** cells = board.getCells();
	// check if any of the blocks reached
	for ( int i = 0; i < 4; i++ )
	{
		if ( currentShape->blockLocationRow[i] == 0 )
		{
			return true;
		}
	}
	// check if a block is next to the current shape from the bottom
	for ( int i = 0; i < 4; i++ )
	{
		if ( cells[currentShape->blockLocationColumn[i]][currentShape->blockLocationRow[i] - 1] == 1 )
		{
			return true;
		}
	}
	return false;
}

void GameStateManager::doMovement()
{
	inputManager.doMovement( &board );
}

void GameStateManager::generateShape()
{
	board.generateShape();
}

void GameStateManager::placeShape()
{
	board.placeShape();
}

bool GameStateManager::deleteFilledRows()
{
	// this algorithm will remove the rows filled when a
	// current shape has been added
	bool** cells = board.getCells();
	int rows = board.getRows();
	int columns = board.getColumns();
	bool result = false;
	bool flag;

	// iterate through rows to find filled blocks
	// if found then delete
	for ( int i = 0; i < rows; i++ ) // for each row
	{
		flag = true;
		for ( int j = 0; j < columns; j++ ) // for each column
		{
			if ( cells[j][i] == 0 ) // check if cell equals to 0
			{
				// if true then that row isnt filled
				flag = false;
				break;
			}
		}

		if ( flag ) // will only enter if a row is filled
		{
			
			// start deleting data by changing current data
			// in that row to 0s
			for ( int j = 0; j < columns; j++ )
			{
				cells[j][i] = 0;
			}
			result = true; // a row was successfully deleted
			leaderboard.incrementScore();
		}
	}


	return result;
}

void GameStateManager::shiftBlocksDown()
{
	bool** cells = board.getCells();
	int rows = board.getRows();
	int columns = board.getColumns();
	bool isEmpty;

	// iterate through the rows to find empty rows
	for ( int i = rows; i >= 0; i-- ) // for each row
	{
		isEmpty = true;
		// iterate through the columns
		for ( int j = 0; j < columns; j++ )
		{
			// for each column check if it contains a 1 in that cell (column, row)
			// if yes then that row isnt empty
			if ( cells[j][i] == 1 )
			{
				isEmpty = false;
				break;
			}
		}

		// if this row is empty
		if ( isEmpty )
		{
			// if a row is empty copy data from the above row to the current
			// until it reached one row from the top
			// for each row on top of the empty row
			for ( int someRow = i; someRow < rows - 1; someRow++ )
			{
				// for a cell with position (someColumn, someRow)
				for ( int someColumn = 0; someColumn < columns; someColumn++ )
				{
					cells[someColumn][someRow] = cells[someColumn][someRow + 1];
				}
			}

			// after copying data from the row above
			// the top row will be duplicated as a result will be turn into 0s
			for ( int someColumn = 0; someColumn < columns; someColumn++ )
			{
				cells[someColumn][rows - 1] = 0;
			}
		}
	}
}

bool GameStateManager::isEndGame()
{
	// checks if the current shape overlaps a block on the board
	Shapes* currentShape = board.getCurrentShape();
	bool** cells = board.getCells();

	for ( int i = 0; i < 4; i++ )
	{
		if ( cells[currentShape->blockLocationColumn[i]][currentShape->blockLocationRow[i]] == 1 )
		{
			return true;
		}
	}
	return false;
}

// this is according to game logic flow diagram
void GameStateManager::playGame() {
	end = std::chrono::system_clock::now();// get current time
	glDuration = end - glTimeStamp; // calculate time taken for block drawing
	sdDuration = end - sdTimeStamp;

	if ( glDuration.count() >= 1.0 / 60 && flag )// did the frame took 1/60 of a second
	{
		// if yes do game logic
		glTimeStamp = current;
		// start for game logic discussed in Game flow logic diagram

		// check right boundary
		if ( rightBoundary() )
		{
			inputManager.unlogKey( 'd' );
			inputManager.unlogKey( 'w' );
		}

		// check left boundary
		if ( leftBoundary() )
		{
			inputManager.unlogKey( 'a' );
			inputManager.unlogKey( 'w' );
		}

		// do Movement
		doMovement();
		// unlog all keys
		inputManager.unlogKeys();

		// check if one second has passed
		if ( sdDuration.count() >= 1.0 / speed )
		{
			frames = 0;
			// check bottom boundary
			if ( bottomBoundary() )
			{
				placeShape();
				//delete filled rows
				if ( deleteFilledRows() )
				{
					// shift all blocks down when a row is deleted
					shiftBlocksDown();
				}
				generateShape();
				printf( "your current score is %i\n", leaderboard.getScore() );
				// check if game over
				if ( isEndGame() )
				{
					printf( "Game over son\n" );
					leaderboard.saveScore( "jacob" );
					flag = false;
					state = 3;
				}
			}
			else
			{
				board.shiftShapeDown();
			}
			sdTimeStamp = current;
		}
	}
	frames++;
	// redraw 
	glutPostRedisplay();
}

void GameStateManager::processMenu( int x, int y )
{
	y = engine.windowHeight - y; // done because the y starts from the top of the window not the bottom
	float worldx = engine.projectWindowWidth * (float)x / (float)engine.windowWidth - (engine.camerax - 0.5); // click position in the world coordinates
	float worldy = engine.projectWindowHeight * (float)y / (float)engine.windowHeight;

	// in main menu
	if ( state == 0 ) 
	{
		int result = inputManager.processMenu( worldx, worldy, engine.main ); // returns the index of the button
		switch ( result )
		{
		case 0: // play game
			board.restartBoard();
			flag = true;
			state = 2;// state to play game
			break;
		case 1:// option menu
			state = 1;// state is option menu
			break;
		case 2:// quit game
			state = 4;// state is quit game
			break;
		}
	}
	// option menu
	else if ( state == 1 )
	{
		int result = inputManager.processMenu( worldx, worldy, engine.option ); // returns the index of the button
		switch ( result )
		{
		case 0: // apply options
			state = 0;// state to main menu
			break;
		case 1:// easy mode
			speed = 1;
			state = 0;
			break;
		case 2:// medium mode
			speed = 4;
			state = 0;
			break;
		case 3:// hard mode
			speed = 10;
			state = 0;
			break;

		}
	}
	// game over menu
	else if ( state == 3 )
	{
		int result = inputManager.processMenu( worldx, worldy, engine.gameOver ); // returns the index of the button
		switch ( result )
		{
		case 0: // play game
			board.restartBoard();
			flag = true;
			leaderboard.saveScore( "jacob" );
			leaderboard.resetCurrentScore();
			state = 2;// state to play game
			break;
		case 1:// main menu menu
			state = 0;// state is option menu
			break;
		case 2:// quit game
			state = 4;// state is quit game
			break;
		}
	}

}

void GameStateManager::displayMainMenu()
{
	engine.renderMenu( engine.main );
}

void GameStateManager::displayOptionMenu()
{
	engine.renderMenu( engine.option );
}

void GameStateManager::displayGameOver()
{
	engine.renderMenu( engine.gameOver );
}