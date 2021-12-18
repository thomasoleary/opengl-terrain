#include "Noise.h"

Noise::Noise()
{
	currentHeight = 0.0f;
	n_heightScale = 3.0f;

	InitNoise();
}

void Noise::GenerateSeed()
{
	srand(time(NULL));
	int seed = rand() % 100 + 1;

	std::cout << "Seed: " << seed << std::endl;
	fNoise.SetSeed(seed);
}

void Noise::InitNoise()
{
	fNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	fNoise.SetFractalType(FastNoiseLite::FractalType_FBm);

	fNoise.SetFractalOctaves(5);

	fNoise.SetFrequency(0.6f);

	std::cout << "Noise Initialised" << std::endl;
}

float Noise::ApplyNoise(int i, int j)
{
	return fNoise.GetNoise(i * 0.03f, j * 0.03f) * n_heightScale;
}
