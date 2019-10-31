#include "Gameboard.h"

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

bool Gameboard::isLeftBoundary()
{
	return leftBoundary;
}

bool Gameboard::isRightBoundary()
{
	return rightBoundary;
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

void Gameboard::setLeftBoundary( bool flag )
{
	leftBoundary = flag;
}

void Gameboard::setRightBoundary( bool flag )
{
	rightBoundary = flag;
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
}

void Gameboard::placeShape()
{
	for ( int i = 0; i < 4; i++ )
	{
		cell[currentShape.blockLocationColumn[i]][currentShape.blockLocationRow[i]] = 1;
	}
	
}