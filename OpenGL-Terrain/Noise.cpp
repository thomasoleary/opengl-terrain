#include "Noise.h"

Noise::Noise()
{
	currentHeight = 0.0f;
	heightScale = 1.0f;
}

void Noise::GenerateSeed()
{
	srand(time(NULL));
	int seed = rand() % 100 + 1;

	fNoise.SetSeed(seed);
}

void Noise::InitNoise()
{
	GenerateSeed();

	fNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	fNoise.SetFractalType(FastNoiseLite::FractalType_FBm);

	fNoise.SetFractalOctaves(5);

	fNoise.SetFrequency(0.6f);
}

void Noise::ApplyNoise(Terrain &terrain)
{
	for (int i = 0; i < terrain.dimension; i++)
	{
		for (int j = 0; j < terrain.dimension; j++)
		{
			Vertex& currentVert = terrain.vertices[i * terrain.dimension + j];
			
			currentHeight = fNoise.GetNoise(i * 0.03f, j * 0.03f) * heightScale;

			currentVert.position.y = currentHeight; // noise stuff
		}
	}
}
