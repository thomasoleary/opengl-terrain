#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain.h"
#include "TerrainType.h"
#include "Shader.h"
#include "Noise.h"

class TerrainGenerator
{
public:
	~TerrainGenerator();

	Terrain terrain = Terrain();
	Noise noise = Noise();

	bool Create(int dimension, float gridSpacing, float heightScale);
	bool Generate();

private:

	bool Init(int dimension, float gridSpacing, float heightScale);
	bool GenerateVertices();
	bool GenerateIndices();
	bool TerrainManager();

	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint indexArrayBufferID;
	GLuint vertexByteSize = sizeof(Vertex);

	int tg_halfDimension;
	float tg_gridSpacing = 0.15f;
};

#endif // !TERRAIN_GENERATOR_H