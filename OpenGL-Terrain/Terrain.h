#pragma once

#include <iostream>

#include <GL/glew.h>
#include "Vertex.h"

class Terrain
{
public:
	Terrain()
	{
		vertices = 0;
		indices = 0;
		numberOfVertices = 0;
		numberOfIndices = 0;
	}
	
	~Terrain()
	{
		delete[] vertices;
		delete[] indices;
		numberOfVertices = 0;
		numberOfIndices = 0;
	}

	Vertex* vertices;
	GLint numberOfVertices;

	GLshort* indices;
	GLint numberOfIndices;

	GLint ReturnVerticeBufferSize() const
	{
		std::cout << "Vertice Buffer Size: " << numberOfVertices * sizeof(Vertex) << std::endl;
		return numberOfVertices * sizeof(Vertex);
	}

	GLint ReturnIndiceBufferSize() const
	{
		std::cout << "Indice Buffer Size: " << numberOfIndices * sizeof(GLshort) << std::endl;
		return numberOfIndices * sizeof(GLshort);
	}
};