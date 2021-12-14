#include "Tank.h"

Tank::Tank()
{
	init();
}
Tank::Tank(int hp)
{
	init(hp);
}
void Tank::init()
{
	maxHP = 100;
	currentHP = maxHP;
	armorFactor = 100;
}
void Tank::init(int hp)
{
	maxHP = hp;
	currentHP = maxHP;
	armorFactor = 100;
}


int Tank::getHP()
{
	return currentHP;
}
int Tank::getMaxHP()
{
	return maxHP;
}
void Tank::setArmor(int arm)
{
	armorFactor = arm;
	armorFactorVL = arm;
}
int Tank::getArmor()
{
	return armorFactor;
}
void Tank::repair()
{
	int currentHP = maxHP;
	armorFactorVL = armorFactor;

}
void Tank::takeDamage(int points)
{
    // as tank gets more damaged, set armorFactor
	//armorFactorVL = armorFactor - Console::mapValue(currentHP, 0, maxHP,10, 0);

	currentHP = currentHP - points; // * (100.0 / armorFactorVL);
}
void Tank::setMaxHP(int h)
{
	maxHP = h;
}
bool Tank::isDead()
{
	return currentHP <= 0;
}
void Tank::setX(int x)
{
	locx = x;
}
void Tank::setY(int y)
{
	locy = y;
}

int Tank::getX()
{
	return locx;
}

int Tank::getY()
{
	return locy;
}



