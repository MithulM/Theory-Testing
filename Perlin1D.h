#pragma once
#include "olcPixelGameEngine.h"
#include <random>
#define WIDTH 1920

class Perlin1D : public olc::PixelGameEngine
{
private:
	float seed[WIDTH] = { 0 };
	
	
	int octaves = 0;
	float bias = 2.0f;

public:
	Perlin1D()
	{
		sAppName = "1-D Perlin";
	}

	bool OnUserCreate() override
	{
		for (int i = 0; i < WIDTH; i++) seed[i] = (float)rand() / (float)RAND_MAX;
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		float noise[WIDTH] = { 0 };

		float scale = 1.0f;
		float total = scale;
		for (int i = 0; i < octaves; i++, scale /= bias, total += scale)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				int step = WIDTH / (2 << i);
				int idx = j / step * step;
				float pitch = (idx == j) ? seed[idx] : lerp(seed[idx], seed[(idx + step)], j % step / (double)step);
				noise[j] += scale * pitch;
			}
		}

		for (int i = 0; i < WIDTH; i++)
			noise[i] *= ScreenHeight() / 2 / total;

		if (GetKey(olc::SPACE).bPressed)
			for (int i = 0; i < WIDTH; i++) seed[i] = (float)rand() / (float)RAND_MAX;

		if (GetKey(olc::W).bPressed)
			octaves++;a

		if (GetKey(olc::D).bPressed)
			bias += 0.2f;
		
		if (GetKey(olc::A).bPressed)
			bias -= 0.2f;

		bias = max(0.2f, bias);

		if (octaves > (int)(log(WIDTH) / log(2)))
			octaves = 0;

		for (int i = 1; i < min(WIDTH, ScreenWidth()); i++)
			DrawLine(olc::vi2d(i, ScreenHeight() / 2 - noise[i]), olc::vi2d(i - 1, ScreenHeight() / 2 - noise[i - 1]), olc::DARK_RED);

		return true;
	}

	float lerp(float val1, float val2, float per)
	{
		return val1 * (1 - per) + val2 * per;
	}
};