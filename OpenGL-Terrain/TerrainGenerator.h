#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain.h"
#include "Shader.h"
#include "Noise.h"

class TerrainGenerator
{
public:
	~TerrainGenerator();

	Terrain terrain = Terrain();
	Noise noise = Noise();

	void GenerateTerrain(int dimension);

	void ApplyNoise(int dimension);

	void TerrainManager();

	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint indexArrayBufferID;
	GLuint vertexByteSize = sizeof(Vertex);


private:
	void InitValues(int dimension);
	void GenerateVertices(int dimension);
	void GenerateIndices(int dimension);


	int halfDimension;
	float gridSpacing = 0.15f;
};

#endif // !TERRAIN_GENERATOR_H