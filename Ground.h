/*

Ground class


By Benjamin Carter - December 14, 2021

This class calculates and stores the ground in the arena.
The class calculates a random ground pattern through the groundRandomizer()

To calculate the random ground, several cosine curves are averaged together. Each magnitude of the cosine curve is a random number from -25 to 25

Then, the ground is saved into the affected array.


*/

#ifndef GROUNDH
#define GROUNDH

#define _USE_MATH_DEFINES
#include <math.h>
#include<chrono> 
#include <random>
#include <iostream>
using namespace std;

class Ground
{
private:
	bool** affected;  // the ground affected array. This just stores if a point is ground or not. 
	int width;
	int height;
public:
	Ground();
	Ground(int w, int h);  // constructors
	void init();
	void init(int w, int h);
	~Ground();
	bool isGround(int x, int y);
	void updateGround(int* ground);   // actions. 
	void groundRandomizer();


};
#endif