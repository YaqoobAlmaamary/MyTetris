#pragma once
#include <GL/glew.h>
#include <iostream>

class Block
{
public:
	GLuint vaoID;
	GLuint vboID;
	GLfloat vxn[36] = { 0 };

	Block()
	{
		vxn[1] = 0.1; vxn[5] = 1;
		vxn[6] = 0.1; vxn[11] = 1;
		vxn[17] = 1;

		vxn[19] = 0.1; vxn[23] = 1;
		vxn[24] = 0.1; vxn[25] = 0.1; vxn[29] = 1;
		vxn[30] = 0.1; vxn[35] = 1;
	
		
	}

	void generateBlock()
	{
		glGenVertexArrays( 1, &vaoID );
		glBindVertexArray( vaoID );
		glGenBuffers( 1, &vboID );
		glBindBuffer( GL_ARRAY_BUFFER, vboID );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vxn ), vxn, GL_STATIC_DRAW );
		
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), 0 );
		glEnableVertexAttribArray( 0 );
	}

};

