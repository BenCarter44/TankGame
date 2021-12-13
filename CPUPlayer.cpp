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
bool CPUPlayer::aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY)
{
	int xe = otherTank->getX() - tank.getX() + 1;
	int ye = otherTank->getY() - tank.getY();
	double gravity = 9.8;
	int maxTheta = 0;
	double maxPower = 0;
	for (int theta = 0; theta < 180; theta++)
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
