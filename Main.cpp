#define OLC_PGE_APPLICATION
#include "Random-Walker.h"

int main()
{
	// Change class to show a certain theory test.

	Walker demo;
	if (demo.Construct(1920, 1080, 1, 1, true))	demo.Start();

	return 0;
}