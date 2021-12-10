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
};
#endif