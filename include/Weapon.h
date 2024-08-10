/*

Weapon class


By Benjamin Carter - December 14, 2021


This class stores information about a weapon. It can store the name, damage, blast, and shotBehavior of the weapon. 

Blast and shotBehavior are not implemented in the game at this time.

*/
#ifndef WEAPONH
#define WEAPONH

#include <string>
using namespace std;
class Weapon
{
private:
	string nameOfWeapon;  // string with the name of the weapon
	int damageFactor;
	int blastRadius;
	int shotBehavior;

public:
	Weapon();
	Weapon(string name);
	Weapon(string name, int damage);
	Weapon(string name, int damage, int blast);
	Weapon(string name, int damage, int blast, int shotBehavior);   // got the constructors

	void init();
	void init(string name);
	void init(string name, int damage);
	void init(string name, int damage, int blast);
	void init(string name, int damage, int blast, int shotBehavior);  // got more "init constructors"
	
	string getName();  // getter methods (read-only!)
	int getDamage();
	int getBlast();
	int getShotB();


};
#endif