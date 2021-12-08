#include "WindowScaler.h"
int inMin;
int inMax;
int outMin;
int outMax;

WindowScaler::WindowScaler()
{
	inMin = 0;
	inMax = 0;
	outMin = 100;
	outMax = 100;
}
void WindowScaler::init()
{
	inMin = 0;
	inMax = 0;
	outMin = 100;
	outMax = 100;
}
WindowScaler::WindowScaler(int i, int j, int k, int l)
{
	inMin = i;
	inMax = j;
	outMin = k;
	outMax = l;
}
void WindowScaler::init(int i, int j, int k, int l)
{
	inMin = i;
	inMax = j;
	outMin = k;
	outMax = l;
}
WindowScaler::WindowScaler(int k, int l)
{
	inMin = 0;
	inMax = 0;
	outMin = k;
	outMax = l;
}
void WindowScaler::init(int k, int l)
{
	inMin = 0;
	inMax = 0;
	outMin = k;
	outMax = l;
}

int WindowScaler::getVal(int i)
{
	return (i - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
double WindowScaler::getDoubleVal(double x)
{
	return (x - inMin) * (outMax - outMin) / (double)(inMax - inMin) + outMin;
}
	
