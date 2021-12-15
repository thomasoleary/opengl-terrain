#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain.h"
#include "TerrainType.h"
#include "Shader.h"

class TerrainGenerator
{
public:
	~TerrainGenerator();

	Terrain terrain = Terrain();

	void GenerateTerrain(int dimension);
	void TerrainManager();

	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint indexArrayBufferID;
	GLuint vertexByteSize = sizeof(Vertex);


private:
	void GenerateVertices(int dimension);
	void GenerateIndices(int dimension);

	float heightScale = 1.0f;
	float gridSpacing = 1.0f;
};

#endif // !TERRAIN_GENERATOR_H