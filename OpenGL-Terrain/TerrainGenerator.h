#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain.h"
#include "Shader.h"

class TerrainGenerator
{
public:
	~TerrainGenerator();

	Terrain terrain = Terrain();

	bool Create(int dimension);

	bool Generate();

	bool TerrainManager();

	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint indexArrayBufferID;
	GLuint vertexByteSize = sizeof(Vertex);


private:
	bool Init(int dimension);
	bool GenerateVertices();
	bool GenerateIndices();


	int halfDimension;
	float gridSpacing = 1.0f;
};

#endif // !TERRAIN_GENERATOR_H