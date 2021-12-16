#include "Noise.h"

Noise::Noise()
{
	// initialise noise stuff
}

void Noise::ApplyNoise(Terrain terrain)
{
	for (int i = 0; i < terrain.dimension; i++)
	{
		for (int j = 0; j < terrain.dimension; j++)
		{
			Vertex& currentVert = terrain.vertices[i * terrain.dimension + j];
			currentVert.position.y = 0.0f; // noise stuff
		}
	}
}
