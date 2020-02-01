#pragma once
#include <GL\glew.h>
#include <SOIL\SOIL.h>
#include <string>
namespace mahSpace {
	class Rectangle
	{
	public:

		// variables
		float x; // this is position in world coordinates
		float y; // this is also in world coordinates
		float width;
		float height;
		const char *texture; // texture location and name

		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		GLuint textureID;
		float data[20];
		GLuint indices[6];
		unsigned char* image;

		// constructors
		Rectangle( float x, float y, float width, float height, const char *texture )
		{
			this->texture = texture;
			// logging data
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;

			// filling data
			// model coordinates												// texture coordinates
			data[0] = x;			data[1] = y;			data[2] = 0.0001;	data[3] = 0;	data[4] = 1;  // top left corner
			data[5] = x + width;	data[6] = y;			data[7] = 0.0001;	data[8] = 1;	data[9] = 1;  // top right corner
			data[10] = x;			data[11] = y - height;	data[12] = 0.0001;	data[13] = 0;	data[14] = 0; // bottom left corner
			data[15] = x + width;	data[16] = y - height;	data[17] = 0.0001;	data[18] = 1;	data[19] = 0; // bottom right corner
			
			// filling indices
			indices[0] = 0;		indices[1] = 1;		indices[2] = 2; // upper triangle
			indices[3] = 1;		indices[4] = 3;		indices[5] = 2; // lower triangle
		}

		Rectangle()
			:
			Rectangle ( 0, 0, 1, 1, "dummy" )
		{}

		// methods
		void initalizeRectangle();


	};
}
