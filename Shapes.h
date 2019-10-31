#pragma once
#include <cstdlib> 
#include <ctime> 

class Shapes
{
private:
	int type;
		

public:
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
	void rotateCounterClockWise();
	void rotateClockWise();
	void shiftDown();
	void formalizeShape();
	
	// constructor
	Shapes()
	{
		srand( time( 0 ) );
	}
};

