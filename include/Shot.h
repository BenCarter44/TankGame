/*

Shot class


By Benjamin Carter - December 14, 2021


This class stores information about the trajectory of a shot 

This is where the points of the trajectory of a shot is calculated.
This class uses the math c++ library to do that. 

The class stors the shot power, angle, and starting X and Y's
Each point is then pushed to the vector of PStruct




*/
#ifndef SHOTH
#define SHOTH

#include "PrettyConsole/point.h"
#include "PStruct.h"
#include "Weapon.h"
#define _USE_MATH_DEFINES
#include <math.h>


class Shot
{
	
	// contains correct power and angle. Also, contains a weapon.
	// game class will have a method that can display a shot.
private:
	vector<PStruct> points;  // points, power, angle, and other information of the shot.
	double power;
	double angle;
	int startX;
	int startY;
	Weapon w;

public:
	void calculatePoints(); // calculate the points given the startX, startY, power, and angle
	vector<PStruct> getPoints(); // get the points calculated

	int getStartX();
	int getStartY();         // get and set
	void setStartX(int x);
	void setStartY(int y);

	void setWeapon(Weapon w2);
	Weapon getWeapon();

	double getPower();
	double getAngle();
	void setPower(double p);
	void setAngle(double a);

	Shot();                           // constructors here ("init constructors" too)
	void init();
	Shot(double p, double a);
	void init(double p, double a);


	// projectile motion. 
	// 
	

};
#endif