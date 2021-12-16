#ifndef NOISE_H
#define NOISE_H
#pragma once

#include <iostream>
#include "FastNoiseLite.h"

class Noise
{
public:
	Noise();

	FastNoiseLite fNoise = FastNoiseLite();

	void InitNoise();
	float ApplyNoise(int i, int j);

	void GenerateSeed();

private:
	float currentHeight;
	int heightScale;
};

#endif // !NOISE_H