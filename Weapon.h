#ifndef WEAPONH
#define WEAPONH

#include <string>
using namespace std;
class Weapon
{
private:
	string nameOfWeapon;
	int damageFactor;
	int blastRadius;
	int shotBehavior;

public:
	Weapon();
	Weapon(string name);
	Weapon(string name, int damage);
	Weapon(string name, int damage, int blast);
	Weapon(string name, int damage, int blast, int shotBehavior);

	void init();
	void init(string name);
	void init(string name, int damage);
	void init(string name, int damage, int blast);
	void init(string name, int damage, int blast, int shotBehavior);
	
	string getName();
	int getDamage();
	int getBlast();
	int getShotB();


};
#endif