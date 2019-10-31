#pragma once
#include "MyShader.h"
#include "Block.h"
#include "Gameboard.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RenderEngine
{
private:
	// variables
	GLuint modelLocation; 
	glm::mat4 identity = glm::mat4( 1 );
	glm::mat4 model = glm::mat4( 1 );
	glm::mat4 view = glm::mat4( 1 );
	glm::mat4 projection = glm::mat4( 1 );

	// methods
	void drawBlocks( Gameboard* board );
	void drawBoard( Gameboard* board );
public:
	// variables
	int windowWidth;
	int windowHeight;
	int counter;

	MyShader mainShader;
	MyShader lightingShader;

	Block* buildingBlocks;
	Block buffer = Block();
	// methods
	void render( Gameboard* board );
	void initData();
	void generateShape();
	

	// constructor
	RenderEngine();
	~RenderEngine();
};

