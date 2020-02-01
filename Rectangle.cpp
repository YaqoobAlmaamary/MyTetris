#include "Rectangle.h"

#include <iostream>

void mahSpace::Rectangle::initalizeRectangle()
{
	// create a vertex array object
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	// buffer to store vertices
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( data ), data, GL_STATIC_DRAW );

	// connect attribute in shader with vbo
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), 0 );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (GLvoid*)( 3 * sizeof( float ) ));
	glEnableVertexAttribArray( 1 );

	// setting up for index drawing
	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

	// Texture related operation
	// generate texture object
	glGenTextures( 1, &textureID );
	glBindTexture( GL_TEXTURE_2D, textureID );
	
	// setting up texture modes in opengl
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// reading image from file
	int width, height;
	int channel = 0;
	image = SOIL_load_image( texture, &width, &height, 0, SOIL_LOAD_RGBA );

	// send image to currently bound texture object
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
//	glGenerateMipmap( GL_TEXTURE_2D );

	// free image from memory
	SOIL_free_image_data( image );

}

