#include "Mesh.h"

Mesh::Mesh( std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures )
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

void Mesh::Draw( MyShader shader )
{
}

void Mesh::setupMesh()
{
}
