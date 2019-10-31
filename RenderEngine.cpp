#include "RenderEngine.h"

// methods
void RenderEngine::render( Gameboard* board )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear screen
	
	drawBlocks( board );

	glutSwapBuffers();
}

void RenderEngine::drawBoard( Gameboard* board )
{
	int columns = board->getColumns();
	int rows = board->getRows();



}

void RenderEngine::drawBlocks( Gameboard* board )
{
	glBindVertexArray( buffer.vaoID ); // bind buffer (Geometric Shape)

	Shapes* currentShape = board->getCurrentShape(); // get the current shape
	bool** cell = board->getCells(); // get the board

	// draw current shape
	for ( int i = 0; i < 4; i++ )
	{
		model = glm::translate( identity, glm::vec3( currentShape->blockLocationColumn[i] * 0.1, currentShape->blockLocationRow[i] * 0.1, 0 ) );
		glUniformMatrix4fv( modelLocation, 1, GL_FALSE, glm::value_ptr( model ) );
		glDrawArrays( GL_TRIANGLES, 0, 6 );
	}

	// draw blocks from board
	int rows = board->getRows();
	int columns = board->getColumns();

	for ( int i = 0; i < rows; i++ )
	{
		for ( int j = 0; j < columns; j++ )
		{
			if ( cell[i][j] == 1 )
			{
				model = glm::translate( identity, glm::vec3( i * 0.1, j * 0.1, 0 ) );
				glUniformMatrix4fv( modelLocation, 1, GL_FALSE, glm::value_ptr( model ) );
				glDrawArrays( GL_TRIANGLES, 0, 6 );

			}
		}
	}
}

void RenderEngine::initData()
{
	// loads and compiles shaders
	mainShader.LoadShaders( "Shaders/Vertex Shader.txt", "Shaders/Fragment Shader.txt" ); 
	lightingShader.LoadShaders( "Shaders/Lighting Vertex Shader.txt", "Shaders/Lighting Fragment Shader.txt" );
	
	// use this as current program
	glUseProgram( mainShader.getProgramID() );

	// set the projection and veiw matrix
	glm::vec3 cameraPosition = glm::vec3( 3.95, 0, 5 );
	projection = glm::perspective( 45.0f, ((float)windowWidth) / (float)windowHeight, 0.1f, 100.0f );
	view = glm::lookAt( cameraPosition, cameraPosition + glm::vec3( 0, 0, -1 ), glm::vec3( 0, 1, 0 ) );
	
	// getting location of shader variables in opengl table
	GLuint projectionLocation = glGetUniformLocation( mainShader.getProgramID(), "projection" );
	GLuint viewLocation = glGetUniformLocation( mainShader.getProgramID(), "view" );
	modelLocation = glGetUniformLocation( mainShader.getProgramID(), "model" );

	// update variables in shader with respect to opengl table
	glUniformMatrix4fv( projectionLocation, 1, GL_FALSE, glm::value_ptr( projection ) );
	glUniformMatrix4fv( viewLocation, 1, GL_FALSE, glm::value_ptr( view ) );
	glUniformMatrix4fv( modelLocation, 1, GL_FALSE, glm::value_ptr( model ) );

	// creates the building blocks
	buildingBlocks = new Block[200];
	buffer.generateBlock();
}
 
void RenderEngine::generateShape()
{
	for( int i = 0; i < 4; i++ )
		buildingBlocks[counter++].generateBlock();
}

// constructors
RenderEngine::RenderEngine()
{
	windowWidth = 1024;
	windowHeight = 720;
	counter = 0;
	
	printf( "hello from the engine\n" );
}

RenderEngine::~RenderEngine()
{
	printf( "engine out\n" );
	delete buildingBlocks;
}