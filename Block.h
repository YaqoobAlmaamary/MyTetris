#pragma once
#include <GL/glew.h>
#include <iostream>

class Block
{
public:
	GLuint vaoID;
	GLuint vboID;
	GLuint colorvboID;
	GLfloat vxn[36] = { 0 };
	GLfloat color[3];
	Block()
	{
		vxn[1] = 0.1f; vxn[5] = 1;
		vxn[6] = 0.1f; vxn[11] = 1;
		vxn[17] = 1;

		vxn[19] = 0.1f; vxn[23] = 1;
		vxn[24] = 0.1f; vxn[25] = 0.1f; vxn[29] = 1;
		vxn[30] = 0.1f; vxn[35] = 1;
		
		// the color 121, 7, 250
		color[0] = 121.0f / 255;
		color[1] = 7.0f / 255;
		color[2] = 250.0f / 255;
		
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

