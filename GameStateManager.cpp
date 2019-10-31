#include "GameStateManager.h"

void GameStateManager::display()
{
	engine.render( &board );
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
}

bool GameStateManager::leftBoundary()
{
	Shapes* currentShape = board.getCurrentShape();
	bool** cells = board.getCells();
	// check if any of the blocks column location is 0
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
	// check if any of the blocks column location is number of columns - 1
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
	// current shape has been added to that row
	Shapes* currentShape = board.getCurrentShape();
	bool** cells = board.getCells();
	int columns = board.getColumns();
	int rows[4];
	bool result = false;

	// get the rows for the current shape
	for ( int i = 0; i < 4; i++ )
	{
		rows[i] = currentShape->blockLocationRow[i];
	}

	// check if a row is filled
	bool flag = true; // will be true if a row in the board is filled with 1s
	for ( int i = 0; i < 4; i++ ) // for each row where the current shape is
	{
		flag = true;
		for ( int j = 0; j < columns; j++ ) // for each column in that row
		{
			if ( cells[j][rows[i]] == 0 ) // if a row contains a 0 then that row isnt filled
			{
				flag = false;
				break;
			}
		}

		if ( flag ) // only true if row is filled
		{
			// it will enter the block only if a row is filled with
			// 1s as a result it will turn that row into 0s
			for ( int currentColumn = 0; currentColumn < columns; currentColumn++ )
			{
				cells[currentColumn][rows[i]] = 0;
			}
			result = true;
		}
	}
	return result;
}

void GameStateManager::shiftBlocksDown()
{
	// this algorithm will search the rows empty after row deletion
	Shapes* currentShape = board.getCurrentShape();
	bool** cells = board.getCells();
	int totalColumns = board.getColumns();
	int totalRows = board.getRows();
	int rows[4];

	// get the rows for the current shape
	for ( int i = 0; i < 4; i++ )
	{
		rows[i] = currentShape->blockLocationRow[i];
	}

	// check if a row is filled
	bool flag = true; // will be true if a row in the board is filled with 1s
	for ( int i = 0; i < 4; i++ ) // for each row where the current shape is
	{
		flag = true;
		for ( int j = 0; j < totalColumns; j++ ) // for each column in that row
		{
			if ( cells[j][rows[i]] == 1 ) // if a row contains a 1 then that row isnt empty
			{
				flag = false;
				break;
			}
		}

		if ( flag ) // only true if row is empty
		{
			// it will enter the block only if a row is filled with
			// 0s as a result it will push the above blocks down
			for ( int currentRow = rows[i]; currentRow < totalRows - 1; currentRow++ )
			{
				for ( int currentColumn = 0; currentColumn < totalColumns; currentColumn++ )
				{
					cells[currentColumn][currentRow] = cells[currentColumn][currentRow + 1];
				}
			}
		}
	}
}

bool GameStateManager::isEndGame()
{
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