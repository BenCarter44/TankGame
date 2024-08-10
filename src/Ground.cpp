/*

Ground class


By Benjamin Carter - December 14, 2021

This class calculates and stores the ground in the arena.
The class calculates a random ground pattern through the groundRandomizer()

To calculate the random ground, several cosine curves are averaged together. Each magnitude of the cosine curve is a random number from -25 to 25

Then, the ground is saved into the affected array.

*/
#include "Ground.h"

Ground::Ground()
{
	width = 0;
	height = 0;
}
Ground::Ground(int w, int h)
{
	width = w;
	height = h;
	affected = new bool* [h];
	for (int row = 0; row < h; row++)
	{
		affected[row] = new bool[w];
		for (int i = 0; i < w; i++)
		{
			affected[row][i] = 0;
		}
	}
}
Ground::~Ground()
{
	if (width != 0 || height != 0)
	{
		for (int row = 0; row < height; row++)
		{
			delete[] affected[row];
		}
		delete[] affected;
	}
}
void Ground::init()
{
	if (width != 0 || height != 0)
	{
		for (int row = 0; row < height; row++)
		{
			delete[] affected[row];
		}
		delete[] affected;
	}
	width = 0;
	height = 0;
}
void Ground::init(int w, int h)
{
	if (width != 0 || height != 0)
	{
		for (int row = 0; row < height; row++)
		{
			delete[] affected[row];
		}
		delete[] affected;
	}
	width = w;
	height = h;
	affected = new bool* [h];
	for (int row = 0; row < h; row++)
	{
		affected[row] = new bool[w];
		for (int i = 0; i < w; i++)
		{
			affected[row][i] = 0;
		}
	}
}

bool Ground::isGround(int x, int y)
{
	return affected[y][x];
}
void Ground::updateGround(int* ground)  // set bars of ones on each column starting at the bottom of the array.
{
	//cout << "apple!\n";
	for (int col = 0; col < width; col++)
	{
		for (int y = height-1; y >= height-ground[col]; y--)
		{
			//cout << y << '\n';
			affected[y][col] = 1;
		}
	}
	/*
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << affected[y][x] << " ";
		}
		cout << '\n';
	}
	*/
}

void Ground::groundRandomizer()
{
	srand(time(0));
	

	/*
	Ground Randomizer.

	Add up a number of cosine (max of 7) functions. 
	Get their average value and put them into the array.
	
	*/


	// create 
	// function = rand  * cos((2 * pi / 200) * x) + 25
	// add and average
	int* randGround = new int[width];
	double* rStore = new double[height / 2];
	for (int r = 0; r < height / 2; r++)
	{
		double n = ((rand() % 100) / 100.0) * height - (height / 2);
		//cout << n << '\n';
		rStore[r] = (double)n;
	}
	//rStore[0] = -25;
	for (int x = 0; x < width; x++)
	{
		double sumOf = 0;
		int max = height / 2;
		if (max > 7)
		{
			max = 7;
		}
		for (int r = 0; r < max; r++)
		{
			double n = rStore[r];
			sumOf = sumOf + n * cos((2.0 * M_PI / (double)(width * 2)) * x * ( r + 1 ) ) + height / 2.0;
		}
		sumOf = sumOf / max;
		sumOf = (sumOf / 1.7);
		randGround[x] = (int)sumOf;
	}
/*	cout << height << '\n';
	cout << width << '\n';
	cout << "HERE!\n";
	for (int x = 0; x < width / 2; x++)
	{
		cout << x << " " <<  randGround[x] << '\n';
	}
	
	*/
	updateGround(randGround);  // put the values into the array.
	
	delete[] rStore;
}