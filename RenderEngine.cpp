#include "RenderEngine.h"

// methods
void RenderEngine::render( Gameboard* board )
{
	glUseProgram( mainShader.getProgramID() );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear screen

	drawBlocks( board );
	drawBoard( board );

	glutSwapBuffers(); // display on screen
}

void RenderEngine::drawBoard( Gameboard* board )
{
	glUniform3fv( colorLocation, 1, line.color );
	glBindVertexArray( line.vaoID );

	int columns = board->getColumns();
	int rows = board->getRows();

	// will draw a line for columns and rows
	for ( int i = 0; i <= columns; i++ ) // for each column
	{
		line.update( i * 0.1f, 0, i * 0.1f, rows * 0.1f );
		glDrawArrays( GL_LINES, 0, 2 );
	}

	for ( int i = 0; i <= rows; i++ )
	{
		line.update( 0, i * 0.1f, columns * 0.1f, i * 0.1f );
		glDrawArrays( GL_LINES, 0, 2 );
	}

}

void RenderEngine::drawBlocks( Gameboard* board )
{
	Shapes* currentShape = board->getCurrentShape(); // get the current shape
	Shapes* shadow = board->getShadow();
	bool** cell = board->getCells(); // get the board

	glUniform3fv( colorLocation, 1, currentShape->color );
	glBindVertexArray( buffer.vaoID ); // bind buffer (Geometric Shape)

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

	for ( int i = 0; i < columns; i++ )
	{
		for ( int j = 0; j < rows; j++ )
		{
			if ( cell[i][j] == 1 )
			{
				model = glm::translate( identity, glm::vec3( i * 0.1, j * 0.1, 0 ) );
				glUniformMatrix4fv( modelLocation, 1, GL_FALSE, glm::value_ptr( model ) );
				glDrawArrays( GL_TRIANGLES, 0, 6 );

			}
		}
	}

	glUniform3fv( colorLocation, 1, shadow->color );
	// draw shadow
	for ( int i = 0; i < 4; i++ )
	{
		
		model = glm::translate( identity, glm::vec3( shadow->blockLocationColumn[i] * 0.1, shadow->blockLocationRow[i] * 0.1, 0 ) );
		glUniformMatrix4fv( modelLocation, 1, GL_FALSE, glm::value_ptr( model ) );
		glDrawArrays( GL_TRIANGLES, 0, 6 );
	}

	model = identity;
	glUniformMatrix4fv( modelLocation, 1, GL_FALSE, glm::value_ptr( model ) );
}

#define PI 3.1415926537
void RenderEngine::initData()
{
	// loads and compiles shaders
	mainShader.LoadShaders( "Shaders/1.Vertex Shader.txt", "Shaders/1.Fragment Shader.txt" ); 
	textureShader.LoadShaders( "Shaders/3.Vertex Shader.txt", "Shaders/3.Fragment Shader.txt" );
	//lightingShader.LoadShaders( "Shaders/Lighting Vertex Shader.txt", "Shaders/Lighting Fragment Shader.txt" );
	
	// use this as current program
	glUseProgram( mainShader.getProgramID() );

	// set the projection and veiw matrix
	cameraz = 2;
	camerax = cameraz * tan( 38.3 * PI / 180 );
	cameray = cameraz * tan ( 28.85 * PI / 180 );
	glm::vec3 cameraPosition = glm::vec3( camerax - (camerax - 0.5), cameray, cameraz );
		// angle is 38.3 when working with x-axis and 28.8 when working with y-axis
	projection = glm::perspective( 45.0f, ((float)windowWidth) / (float)windowHeight, 0.1f, 100.0f ); 
	view = glm::lookAt( cameraPosition, cameraPosition + glm::vec3( 0, 0, -1 ), glm::vec3( 0, 1, 0 ) );
	
	// getting location of shader variables in opengl table
	GLuint projectionLocation = glGetUniformLocation( mainShader.getProgramID(), "projection" );
	GLuint viewLocation = glGetUniformLocation( mainShader.getProgramID(), "view" );
	modelLocation = glGetUniformLocation( mainShader.getProgramID(), "model" );
	colorLocation = glGetUniformLocation ( mainShader.getProgramID(), "color" );

	// update variables in shader with respect to opengl table
	glUniformMatrix4fv( projectionLocation, 1, GL_FALSE, glm::value_ptr( projection ) );
	glUniformMatrix4fv( viewLocation, 1, GL_FALSE, glm::value_ptr( view ) );
	glUniformMatrix4fv( modelLocation, 1, GL_FALSE, glm::value_ptr( model ) );

	// creates the building blocks
	buffer.generateBlock();
	line.generateLine();

	// test stuff
	projectWindowWidth = 2 * camerax; // 38.3 because calulated shit 
	projectWindowHeight = 2 * cameray; // same goes for 28.8
}

void RenderEngine::initMenus( float boardWidth, float boardHeight )
{
	glUseProgram( textureShader.getProgramID() );

	GLuint projectionLocation = glGetUniformLocation( textureShader.getProgramID(), "projection" );
	GLuint viewLocation = glGetUniformLocation( textureShader.getProgramID(), "view" );

	glUniformMatrix4fv( projectionLocation, 1, GL_FALSE, glm::value_ptr( projection ) );	
	glUniformMatrix4fv( viewLocation, 1, GL_FALSE, glm::value_ptr( view ) );

	float buttonWidth = 0.7791;
	float buttonHeight = 0.3;
	// initializing main menu
	float displacementX = 0;
	mahSpace::Rectangle playButton( displacementX, boardHeight *0.9, buttonWidth, buttonHeight, "Textures/play.jpg" );
	mahSpace::Rectangle optionButton( displacementX, boardHeight * 0.7, buttonWidth, buttonHeight, "Textures/option.jpg" );
	mahSpace::Rectangle exitButton( displacementX, boardHeight * 0.15, buttonWidth, buttonHeight, "Textures/exit.jpg" );
	mahSpace::Rectangle backGround( 0, 0, boardWidth, boardHeight, "Textures/black.jpg" );

	main.addButton( playButton ); // index 0
	main.addButton( optionButton ); // index 1
	main.addButton( exitButton ); // index 2
	main.initMenu();

	// initializing option menu
	int displacementx2 = -boardWidth;
	mahSpace::Rectangle apply( displacementx2, boardHeight * 0.15, buttonWidth, buttonHeight, "Textures/apply.jpg" ); // index 0
	mahSpace::Rectangle easy( displacementx2, boardHeight * 0.8, buttonWidth, buttonHeight, "Textures/easy.jpg" ); // index 1
	mahSpace::Rectangle medium( displacementx2, boardHeight * 0.6, buttonWidth, buttonHeight, "Textures/medium.jpg" ); // index 2
	mahSpace::Rectangle hard( displacementx2, boardHeight * 0.4, buttonWidth, buttonHeight, "Textures/hard.jpg" ); // index 3

	option.addButton( apply );
	option.addButton( easy );
	option.addButton( medium );
	option.addButton( hard );
	option.initMenu();

	// initializing gameOver menu
	mahSpace::Rectangle restart( displacementX, boardHeight * 0.9, buttonWidth, buttonHeight, "Textures/restart.jpg" ); // index 0
	mahSpace::Rectangle MainMenu( displacementX, boardHeight * 0.7, buttonWidth, buttonHeight, "Textures/mainMenu.jpg" ); // index 1
	mahSpace::Rectangle quit( displacementX, boardHeight * 0.15, buttonWidth, buttonHeight, "Textures/exit.jpg" ); // index 2

	gameOver.addButton( restart );
	gameOver.addButton( MainMenu );
	gameOver.addButton( quit );
	gameOver.initMenu();
}


void RenderEngine::renderMenu( Menu menu )
{
	glUseProgram( textureShader.getProgramID() );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	for ( int i = 0; i < menu.buttons.size(); i++ )
	{
		glBindTexture( GL_TEXTURE_2D, menu.buttons[i].textureID );
		glBindVertexArray( menu.buttons[i].vao );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	}

	glutSwapBuffers();
}

 
// constructors
RenderEngine::RenderEngine()
{
	windowWidth = 1024;
	windowHeight = 720;
	
	printf( "hello from the engine\n" );
}

RenderEngine::~RenderEngine()
{
	printf( "engine out\n" );
}