#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "Terrain.h"

class TerrainGenerator
{
public:
	Terrain terrain = Terrain();

	int Dimension = 10;

	void GenerateTerrain(int dimension);

private:
	void GenerateVertices(int dimension);
	void GenerateIndices(int dimension);

	float heightScale = 1.0f;
	float gridSpacing = 1.0f;
};

