/*

CPUPlayer class


By Benjamin Carter - December 14, 2021

This class extends the Player class, specifically for a computer player.


This class contains a pointer to the opponent's tank.
This allows for it to aim accurately.

The CPUPlayer calculates the shot under the aimMenu method.

The difficulty determines how far/close the shot will be to the opponent.

100 is far 1 is close.



*/

#include "CPUPlayer.h"


CPUPlayer::CPUPlayer() : Player()
{
	isCPU = true;
}
CPUPlayer::CPUPlayer(string name) : Player(name)
{
	isCPU = true;
}
void CPUPlayer::init()
{
	Player::init();
	isCPU = true;
}
void CPUPlayer::init(string name)
{
	Player::init(name);
	isCPU = true;
}

void CPUPlayer::saveOtherTank(Tank* t)
{
	otherTank = t;
}
bool CPUPlayer::aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY)  // calculate the right angle and power. I had to dervive the formuala.
{
	int xe = otherTank->getX() - tank.getX() + 1;
	int ye = otherTank->getY() - tank.getY();
	srand(time(0));

	int offsetN = (rand() % difficulty) * ((rand() % 2) * -1); // adjusts the power, -100 t0 100

	xe = xe + offsetN / 2;
	
	offsetN = (rand() % difficulty) * ((rand() % 2) * -1);
	ye = ye + offsetN / 10;



	double gravity = 9.8;
	int maxTheta = 0;
	double maxPower = 0;
	for (int theta = 0; theta < 90; theta++)
	{

		double top = (-1.0 * gravity * xe * xe);
		double bottom = (ye - tan(theta * M_PI / 180.0) * xe) * (cos(theta * M_PI / 180.0) * cos(theta * M_PI / 180.0)) * 2.0;
		double power = top / bottom;
		if (power > 0)
		{
			power = sqrt(power);
			if (power <= 33.0)
			{
				maxPower = power;
				maxTheta = theta;
			}
		}
	}
	for (int theta = 180; theta > 90; theta--)
	{

		double top = (-1.0 * gravity * xe * xe);
		double bottom = (ye - tan(theta * M_PI / 180.0) * xe) * (cos(theta * M_PI / 180.0) * cos(theta * M_PI / 180.0)) * 2.0;
		double power = top / bottom;
		if (power > 0)
		{
			power = sqrt(power);
			if (power <= 33.0)
			{
				maxPower = power;
				maxTheta = theta;
			}
		}
	}


	vector<Stash*> sw = getWeapons();

	int maxDamage = 0;
	int count = 0;

	for (int x = 0; x < sw.size(); x++)
	{
		if (sw[x]->getWeaponType().getDamage() > maxDamage)
		{
			maxDamage = sw[x]->getWeaponType().getDamage();
			count = x;
		}
	}
	if (sw.size() == 0)
	{
		return false;
	}

	// randomization
	srand(time(0));
	/*int offsetN = (rand() % difficulty) * ((rand() % 2) * -1); // adjusts the power
	
	double of = offsetN / 3.0;
	maxPower = maxPower + of;
	int offsetA = (rand() % difficulty) * ((rand() % 2) * -1);

	double af = offsetA * .15;
	maxTheta = maxTheta + af;
	*/

	shotHold.init();
	shotHold.setStartX(tank.getX());
	shotHold.setStartY(tank.getY());
	shotHold.setAngle(maxTheta);
	shotHold.setPower(maxPower);
	shotHold.setWeapon(sw[count]->useUpWeapon());



}
Shot CPUPlayer::aimShot()
{
	return shotHold;
}
