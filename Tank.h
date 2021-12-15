/*

Tank class


By Benjamin Carter - December 14, 2021


This class stores information about a tank, such as maxHP, currentHP, armor, and location.
The armor factor is not implemented at this time.

There are some methods that interact with the tank, such as takeDamage or repair which do as expected.

*/

#ifndef TANKH
#define TANKH

#include "PrettyConsole/console.h" // for map

class Tank
{
private:
	int maxHP;
	int currentHP;
	int armorFactor;
	int armorFactorVL;
	int locx;
	int locy;
	 // armorFactor. 100 means average. If the armorFactor is greater, it is stronger. if 200, then half of the points that tank gets are counted
public:
	Tank();
	void init();
	Tank(int hp);
	void init(int hp);
	int getHP();
	int getMaxHP();
	void setArmor(int arm);
	int getArmor();
	bool isDead();
	void takeDamage(int points);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void repair();
	void setMaxHP(int h);
	void setHP(int h);
};
#endif