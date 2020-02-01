#pragma once
#include "MyShader.h"
#include "Block.h"
#include "Line.h"
#include "Gameboard.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Menu.h"

class RenderEngine
{
private:
	// variables
	GLuint modelLocation; 
	GLuint colorLocation;
	glm::mat4 identity = glm::mat4( 1 );
	glm::mat4 model = glm::mat4( 1 );
	glm::mat4 view = glm::mat4( 1 );
	glm::mat4 projection = glm::mat4( 1 );



	// methods
	void drawBlocks( Gameboard* board );
	void drawBoard( Gameboard* board );
public:
	// variables
		// window data
	int windowWidth;
	int windowHeight;

		// shaders
	MyShader mainShader;
	MyShader lightingShader;
	MyShader textureShader;

		// new variables
	Menu main;
	Menu option;
	Menu gameOver;

		// test variables
	float projectWindowWidth;
	float projectWindowHeight;
	float cameraz;
	float camerax;
	float cameray;

		// building blocks
	Line line;
	Block buffer;
	// methods
	void render( Gameboard* board );
	void renderMenu( Menu menu );
	void initData();
	void initMenus( float boardWidth, float boardHeight );

	// constructor
	RenderEngine();
	~RenderEngine();
};

