#ifndef SHOTH
#define SHOTH

#include "PrettyConsole/point.h"
#include "PStruct.h"
#define _USE_MATH_DEFINES
#include <math.h>
// #include <iostream>

class Shot
{
	
	// contains correct power and angle. Also, contains a weapon.
	// game class will have a method that can display a shot.
private:
	vector<PStruct> points;
	double power;
	double angle;
	int startX;
	int startY;

public:
	void calculatePoints();
	vector<PStruct> getPoints();

	int getStartX();
	int getStartY();
	void setStartX(int x);
	void setStartY(int y);


	double getPower();
	double getAngle();
	void setPower(double p);
	void setAngle(double a);

	Shot();
	void init();
	Shot(double p, double a);
	void init(double p, double a);


	// projectile motion. 
	// 
	

};
#endif