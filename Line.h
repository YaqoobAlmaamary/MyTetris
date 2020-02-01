#pragma once
#include <GL/glew.h>

class Line
{
public:
	GLuint vaoID;
	GLuint vboID;
	GLfloat location[6] = { 0 };
	GLfloat color[3] = { 0 };

	Line()
	{
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
	}

	void update( float startx, float starty, float endx, float endy )
	{
		location[0] = startx;
		location[1] = starty;
		location[2] = 0.0001f;
		location[3] = endx;
		location[4] = endy;
		location[5] = 0.0001f;

		glBindBuffer( GL_ARRAY_BUFFER, vboID );
		glBufferData( GL_ARRAY_BUFFER, sizeof( location ), location, GL_STATIC_DRAW );
	}

	void generateLine()
	{
		glGenVertexArrays( 1, &vaoID );
		glBindVertexArray( vaoID );

		glGenBuffers( 1, &vboID );
		glBindBuffer( GL_ARRAY_BUFFER, vboID );
		glBufferData( GL_ARRAY_BUFFER, sizeof( location ), location, GL_STATIC_DRAW );

		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		glEnableVertexAttribArray( 0 );

	}








};

