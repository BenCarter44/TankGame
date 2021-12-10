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
	bool** affected;
	int width;
	int height;
public:
	Ground();
	Ground(int w, int h);
	void init();
	void init(int w, int h);
	~Ground();
	bool isGround(int x, int y);
	void updateGround(int* ground);
	void groundRandomizer();


};
#endif