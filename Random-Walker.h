/*

What it does:
	Makes a path from left middle of the screen to the right end of the screen.

Why:
	To visualize how unstable unifrom random can get.

*/

#pragma once
#include "olcPixelGameEngine.h"
#include <random>

class Walker : public olc::PixelGameEngine
{
private:
	int func(int& t, double a, double& b)  // The random function.
	{
		return (a * t) / (t + a * b);
	}
public:
	Walker()
	{
		sAppName = "Walker";
	}

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Uncomment the line below to show a single possible random walking path.

		// Clear(olc::BLACK);
		const int HALF_RAND = 50;									// The higher the value, the bigger the distribution
		double B = .6;												// The lower the value, the more stable it is.


		// mersenne twister random setup.
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, HALF_RAND * 2 - 1);

		int step = 0;
		int step1 = 0;
		int step2 = 0;

		// Draws the path of three different random approaches.
		for (int i = 0; i < ScreenWidth(); i++)
		{
			int ran = dist(mt);										// Random number.

			// 50/50 chance of going in either direction.
			Draw(olc::vi2d(i, step + ScreenHeight() / 2), olc::WHITE);
			if (ran < HALF_RAND)
				step++;
			else
				step--;

			// Path based on rational function (The further you go from center, the lower changes of going that way)
			Draw(olc::vi2d(i, step2 + ScreenHeight() / 2), olc::BLUE);
			if (ran < HALF_RAND - func(step2, HALF_RAND, B))
				step2++;
			else
				step2--;

			// Path based on linear function (The further you go from center, the lower changes of going that way)
			Draw(olc::vi2d(i, step1 + ScreenHeight() / 2), olc::RED);
			if (ran < HALF_RAND - step1)
				step1++;
			else
				step1--;
		}

		return true;
	}
};