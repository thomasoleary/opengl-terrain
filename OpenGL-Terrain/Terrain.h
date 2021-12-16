#ifndef TERRAIN_H
#define TERRAIN_H

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
		dimension = 0;

		std::cout << "\nTerrain Initialised" << std::endl;
	}
	
	~Terrain()
	{
		delete[] vertices;
		delete[] indices;
		numberOfVertices = 0;
		numberOfIndices = 0;

		std::cout << "Terrain Destroyed" << std::endl;
	}

	int dimension;

	Vertex* vertices;
	int numberOfVertices;

	short* indices;
	int numberOfIndices;

	int ReturnVertexBufferSize() const
	{
		std::cout << "Vertice Buffer Size: " << numberOfVertices * sizeof(Vertex) << std::endl;
		return numberOfVertices * sizeof(Vertex);
	}

	int ReturnIndexBufferSize() const
	{
		std::cout << "Indice Buffer Size: " << numberOfIndices * sizeof(short) << std::endl;
		return numberOfIndices * sizeof(short);
	}
};

#endif // !TERRAIN_H