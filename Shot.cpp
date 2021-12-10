#include "Shot.h"

// window is 100 by 50
// max power is 33
// allows for hitting 100m at ~60deg

// angle adjusted all 360



Shot::Shot()
{
	power = 5;
	angle = 5;
	startX = 0;
	startY = 0;
}
Shot::Shot(double p, double a)
{
	power = p;
	angle = a;
	startX = 0;
	startY = 0;
}
void Shot::init()
{
	power = 5;
	angle = 5;
	startX = 0;
	startY = 0;
}
void Shot::init(double p, double a)
{
	power = p;
	angle = a;
	startX = 0;
	startY = 0;
}

double Shot::getAngle()
{
	return angle;
}
double Shot::getPower()
{
	return power;
}
void Shot::setPower(double p)
{
	power = p;
}
void Shot::setAngle(double a)
{
	angle = a;
}
vector<PStruct> Shot::getPoints()
{
	return points;
}
int Shot::getStartX()
{
	return startX;
}
int Shot::getStartY()
{
	return startY;
}
void Shot::setStartX(int x)
{
	startX = x;
}
void Shot::setStartY(int y)
{
	startY = y;
}

void Shot::calculatePoints()
{
	using namespace std;
	// all projectiles will have the same "speed"

	double radAngle = angle * M_PI / 180.0;
	double gravity = 9.8;


	/*
	
	y(x) = function. plugX = (x - x0) 
	
	
	*/
	if ((angle < 90.0 && angle > 0) || angle > 270.0)
	{
		for (double x = 0; x < 100; x = x + 0.1)
		{
			double plugX = x - startX;
			double function = tan(radAngle) * plugX - gravity * plugX * plugX / (2 * power * power * cos(radAngle) * cos(radAngle)) + startY;
			// Point2D* pt = new Point2D(x + startX, (int)function + startY);
			PStruct pt;
			pt.x = x;
			pt.y = function;
			if (x >= startX)
			{
				points.push_back(pt);
			}
		}
	}
	else if (angle < 270.0 && angle > 90.0)
	{
		for (double x = 0; x > -100; x = x - 0.1)
		{
			double plugX = x;
			double function = tan(radAngle) * plugX - gravity * plugX * plugX / (2 * power * power * cos(radAngle) * cos(radAngle)) + startY;
			//Point2D* pt = new Point2D(x + startX, (int)function + startY);
			// Point2D* pt = new Point2D(x + startX, (int)function + startY);
			PStruct pt;
			pt.x = x + startX;
			pt.y = function;
			if (x <= startX)
			{
				points.push_back(pt);
			}
		}
	}
	else if (angle == 90.0 || angle == 270.0)
	{
		for (double x = 0; x < 100; x = x + 0.1)
		{
			// x is time in this case
			double plugX = startX;
			double function = power * sin(radAngle) +  -1 * gravity * x * x / 2.0;
			//Point2D* pt = new Point2D(startX, (int)function + startY);
			// Point2D* pt = new Point2D(x + startX, (int)function + startY);
			PStruct pt;
			pt.x = startX;
			pt.y = function + startY;
			points.push_back(pt);
		}
	}
	
	

}