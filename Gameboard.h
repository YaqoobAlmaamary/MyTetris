#pragma once
#include "Shapes.h"

class Gameboard
{
private:
	int columns;
	int rows;
	bool** cell; // order is first row and then column not the way i now think which column and then row
	Shapes currentShape;
	Shapes shadow;

public:

	Gameboard()
	{
		columns = 10;
		rows = 10;

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

	}

	Gameboard( int width, int height )
	{
		this->columns = width;
		this->rows = height;
		
		cell = new bool *[columns];
		for ( int i = 0; i < columns; i++ )
			cell[i] = new bool[rows];

		for ( int i = 0; i < rows; i++ )
		{
			for ( int j = 0; j < columns; j++ )
			{
				cell[j][i] = 0;
			}
		}
	}

	~Gameboard()
	{
		for ( int i = 0; i < columns; i++ )
		{
			delete[] cell[i];
		}
		delete[] cell;
	}

	int getColumns();
	int getRows();
	bool** getCells();
	Shapes* getCurrentShape();
	Shapes* getShadow();

	void setColumns( int width );
	void setRows( int height );

	void generateShape();
	void placeShape();

	void pushShapeDown(); // pushes the current shape down more quickly
	void calculateShadow(); // calculate the shadow position of the current shape

	void shiftShapeRight(); // shifts the current shape to right
	void shiftShapeLeft(); // shifts the current shape to left
	void rotateCounterClockWise(); // rotates current shape
	void shiftShapeDown(); // shifts the current shape down

	void restartBoard();

};

