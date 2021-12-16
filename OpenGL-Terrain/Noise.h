#ifndef NOISE_H
#define NOISE_H
#pragma once

#include "Terrain.h"
#include "FastNoiseLite.h"

class Noise
{
public:
	Noise();

	Terrain noiseTerrain;
	FastNoiseLite fNoise = FastNoiseLite();

	void InitNoise();
	void ApplyNoise(Terrain &terrain);

	void GenerateSeed();

private:
	float currentHeight;
	int heightScale;
};

#endif // !NOISE_H