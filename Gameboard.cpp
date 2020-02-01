#include "Gameboard.h"
#include <iostream>

// getters
int Gameboard::getColumns()
{
	return columns;
}

int Gameboard::getRows()
{
	return rows;
}

bool** Gameboard::getCells()
{
	return cell;
}

Shapes* Gameboard::getCurrentShape()
{
	return &currentShape;
}

Shapes* Gameboard::getShadow()
{
	return &shadow;
}

// setters
void Gameboard::setColumns( int width )
{
	this->columns = width;
}

void Gameboard::setRows( int height )
{
	this->rows = height;
}

// other methods
void Gameboard::generateShape()
{
	currentShape.formalizeShape();
	for ( int i = 0; i < 4; i++ )
	{
		currentShape.blockLocationRow[i] = currentShape.blockInitRow[i] + rows - 1;
		currentShape.blockLocationColumn[i] = currentShape.blockInitColumn[i] + columns - 3;
	}
	currentShape.pivotLocationColumn = currentShape.blockLocationColumn[0];
	currentShape.pivotLocationRow = currentShape.blockLocationRow[0];

	shadow = Shapes( &currentShape );
	calculateShadow();
}

void Gameboard::placeShape()
{
	for ( int i = 0; i < 4; i++ )
	{
		cell[currentShape.blockLocationColumn[i]][currentShape.blockLocationRow[i]] = 1;
	}
	
}


void Gameboard::calculateShadow()
{
	// will calculate the distance from current block to the nearest
	// block on the board. To be more precise steps for the current block
	// to lay on top of the block on the board
	int smallest = rows;
	int counter = 0;
	int buffer = 0;
	for ( int i = 0; i < 4; i++ ) // for each block in the shape
	{
		for ( int j = currentShape.blockLocationRow[i]; ; j--, counter++ )
		{
			if ( j == 0 || cell[currentShape.blockLocationColumn[i]][j - 1] == 1 )
			{
				buffer = counter;
				break;
			}
		}

		if ( counter <= smallest )
		{
			smallest = counter;
		}
		counter = 0;
	}

	for ( int i = 0; i < 4; i++ )
	{
		shadow.blockLocationColumn[i] = currentShape.blockLocationColumn[i];
		shadow.blockLocationRow[i] = currentShape.blockLocationRow[i] - smallest;
	}
	

}

void Gameboard::shiftShapeLeft()
{
	currentShape.shiftLeft();
	calculateShadow();
}

void Gameboard::shiftShapeRight()
{
	currentShape.shiftRight();
	calculateShadow();
}

void Gameboard::rotateCounterClockWise()
{
	currentShape.rotateClockWise();
	calculateShadow();
}

void Gameboard::shiftShapeDown()
{
	currentShape.shiftDown();
	calculateShadow();
}

void Gameboard::pushShapeDown()
{
	for ( int i = 0; i < 4; i++ )
	{
		currentShape.blockLocationColumn[i] = shadow.blockLocationColumn[i];
		currentShape.blockLocationRow[i] = shadow.blockLocationRow[i];
	}

}

void Gameboard::restartBoard()
{
	for ( int i = 0; i < columns; i++ )
	{
		delete[] cell[i];
	}
	delete[] cell;

	cell = new bool* [columns];
	for ( int i = 0; i < columns; i++ )
		cell[i] = new bool[rows];

	for ( int i = 0; i < rows; i++ )
	{
		for ( int j = 0; j < columns; j++ )
		{
			cell[j][i] = 0;
		}
	}
	generateShape();
}
