#include "Shapes.h"
#include <iostream>

void Shapes::shiftLeft()
{
	for ( int i = 0; i < 4; i++ )
	{
		blockLocationColumn[i]--;
	}
	pivotLocationColumn--;

}

void Shapes::shiftRight()
{
	for ( int i = 0; i < 4; i++ )
	{
		blockLocationColumn[i]++;
	}
	pivotLocationColumn++;
}

void Shapes::rotateCounterClockWise()
{
	// we multiply init block location by the rotation matrix 
	// and then displacing the rotated shape by pivot location
	for ( int i = 0; i < 4; i++ )
	{
		int tmp = blockInitColumn[i];
		blockInitColumn[i] = -1 * blockInitRow[i];
		blockInitRow[i] = tmp;
		blockLocationColumn[i] = blockInitColumn[i] + pivotLocationColumn;
		blockLocationRow[i] = blockInitRow[i] + pivotLocationRow;
	}
}

void Shapes::rotateClockWise()
{
	// we multiply init block location by the rotation matrix 
	// and then displacing the rotated shape by pivot location
	for ( int i = 0; i < 4; i++ )
	{
		int tmp = blockInitColumn[i];
		blockInitColumn[i] = blockInitRow[i];
		blockInitRow[i] = -1 * tmp;
		blockLocationColumn[i] = blockInitColumn[i] + pivotLocationColumn;
		blockLocationRow[i] = blockInitRow[i] + pivotLocationRow;
	}
}

void Shapes::shiftDown()
{
	printf( "block Row:%i\n", blockLocationRow[0] );
	for ( int i = 0; i < 4; i++ )
	{
		blockLocationRow[i]--;
	}
	pivotLocationRow--;
	
}

void Shapes::formalizeShape()
{
	type = rand() % 7;

	// pivot block( 0, 0 )
	blockInitColumn[0] = 0;
	blockInitRow[0] = 0;

	// line shape
	if ( type == 0 )
	{
		// ( 1, 0 )
		blockInitColumn[1] = 1;
		blockInitRow[1] = 0;

		// ( 2, 0 )
		blockInitColumn[2] = -1;
		blockInitRow[2] = 0;

		// ( -1, 0 )
		blockInitColumn[3] = -2;
		blockInitRow[3] = 0;
	}

	// s shape
	if ( type == 1 )
	{
		// ( 1, 0 )
		blockInitColumn[1] = 1;
		blockInitRow[1] = 0;

		// ( 0, -1 )
		blockInitColumn[2] = 0;
		blockInitRow[2] = -1;

		// ( -1, -1 )
		blockInitColumn[3] = -1;
		blockInitRow[3] = -1;

	}

	// z shape
	if ( type == 2 )
	{
		// ( -1, 0 )
		blockInitColumn[1] = -1;
		blockInitRow[1] = 0;

		// ( 0, -1 )
		blockInitColumn[2] = 0;
		blockInitRow[2] = -1;

		// ( 1, -1 )
		blockInitColumn[3] = 1;
		blockInitRow[3] = -1;

	}

	// square shape
	if ( type == 3 )
	{
		// ( -1, 0 )
		blockInitColumn[1] = 0;
		blockInitRow[1] = 1;

		// ( -1, -1 )
		blockInitColumn[2] = -1;
		blockInitRow[2] = -1;

		// ( 0, -1 )
		blockInitColumn[3] = 0;
		blockInitRow[3] = -1;

	}

	// l shape
	if ( type == 4 )
	{
		// ( -1, 0 )
		blockInitColumn[1] = -1;
		blockInitRow[1] = 0;

		// ( 0, -1 )
		blockInitColumn[2] = 0;
		blockInitRow[2] = -1;

		// ( 0, -2 )
		blockInitColumn[3] = 0;
		blockInitRow[3] = -2;

	}

	// mirrored l shape
	if ( type == 5 )
	{
		// ( 1, 0 )
		blockInitColumn[1] = 0;
		blockInitRow[1] = 1;

		// ( 0, -1 )
		blockInitColumn[2] = 0;
		blockInitRow[2] = -1;

		// ( 0, -2 )
		blockInitColumn[3] = 0;
		blockInitRow[3] = -2;

	}

	// t shape
	if ( type == 6 )
	{
		// ( 1, 0 )
		blockInitColumn[1] = 1;
		blockInitRow[1] = 0;

		// ( 0, -1 )
		blockInitColumn[2] = 0;
		blockInitRow[2] = -1;

		// ( -1, 0 )
		blockInitColumn[3] = -1;
		blockInitRow[3] = 0;

	}
}
