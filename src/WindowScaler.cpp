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
int WindowScaler::reverse(int absolutePixel)
{
	int great = (outMax > outMin) ? outMax : outMin;
	return ((absolutePixel * (inMax - inMin)) / (great - 1)) + inMin;
}
int WindowScaler::getVal(int i)
{
	return (double)(i - inMin) * (double)(outMax - outMin) / (double)(inMax - inMin) + outMin;
}
double WindowScaler::getDoubleVal(double x)
{
	return (double)(x - inMin) * (double)(outMax - outMin) / (double)(inMax - inMin) + outMin;
}
int WindowScaler::getLength(int i)
{
	if ((inMin > inMax || outMin > outMax) && !(inMin > inMax && outMin > outMax))
	{
		// flipped!
		return outMax - getVal(i);
	}
	else
	{
		return getVal(i);
	}
}

int WindowScaler::getOutMax()
{
	return outMax;
}
int WindowScaler::getOutMin()
{
	return outMin;
}
int WindowScaler::getInMax()
{
	return inMax;
}
int WindowScaler::getInMin()
{
	return inMin;
}