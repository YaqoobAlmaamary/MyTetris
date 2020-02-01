#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "MyShader.h"

// this class will be used to add 3D scenes behind the gameboard
// currently not functional and not used anywhere
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoor;
};

struct Texture
{
	unsigned int id;
	std::string type;
};

class Mesh
{
public: 
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh( std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures );
	void Draw( MyShader shader );
private:
	// render data
	GLuint VAO, VBO, EBO;
	// functions
	void setupMesh();

};

