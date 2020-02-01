#pragma once
#include <cstdlib> 
#include <ctime> 

class Shapes
{
private:
	int type;
		

public:
	float color[3];
	// variables
	int blockInitColumn[4];
	int blockInitRow[4];

	int pivotLocationColumn;
	int pivotLocationRow;

	int blockLocationColumn[4];
	int blockLocationRow[4];

	// methods
	void shiftLeft();
	void shiftRight();
	void shiftDown();
	void rotateCounterClockWise();
	void rotateClockWise();
	void formalizeShape();
	
	// constructor
	Shapes()
	{
		srand( time( 0 ) );
		// the color 121, 7, 250
		color[0] = 121.0f / 255;
		color[1] = 7.0f / 255;
		color[2] = 250.0f / 255;
	}

	Shapes( Shapes* shape )
	{
		for ( int i = 0; i < 4; i++ )
		{
			blockInitColumn[i] = shape->blockInitColumn[i];
			blockInitRow[i] = shape->blockInitRow[i];
			blockLocationColumn[i] = shape->blockLocationColumn[i];
			blockLocationRow[i] = shape->blockLocationRow[i];
		}
		pivotLocationColumn = shape->pivotLocationColumn;
		pivotLocationRow = shape->pivotLocationRow;

		// lavander 222, 217, 240
		color[0] = 222.0f / 255;
		color[1] = 217.0f / 255;
		color[2] = 240.0f / 255;

	}
};

