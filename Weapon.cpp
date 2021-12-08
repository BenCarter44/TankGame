
#include "Weapon.h"
Weapon::Weapon()
{
	init();
}
Weapon::Weapon(string name)
{
	init(name);
}
Weapon::Weapon(string name, int damage)
{
	init(name, damage);
}
Weapon::Weapon(string name, int damage, int blast)
{
	init(name, damage, blast);
}
Weapon::Weapon(string name, int damage, int blast, int shotBehavior)
{
	init(name, damage, blast, shotBehavior);
}
void Weapon::init()
{
	nameOfWeapon = "Weapon";
	damageFactor = 1;
	blastRadius = 1;
	shotBehavior = 1;
}
void Weapon::init(string name)
{
	nameOfWeapon = name;
	damageFactor = 1;
	blastRadius = 1;
	shotBehavior = 1;
}
void Weapon::init(string name, int damage)
{
	nameOfWeapon = name;
	damageFactor = damage;
	blastRadius = 1;
	shotBehavior = 1;
}
void Weapon::init(string name, int damage, int blast)
{
	nameOfWeapon = name;
	damageFactor = damage;
	blastRadius = blast;
	shotBehavior = 1;
}
void Weapon::init(string name, int damage, int blast, int shotBehavior)
{
	nameOfWeapon = name;
	damageFactor = damage;
	blastRadius = blast;
	this->shotBehavior = shotBehavior;
}
string Weapon::getName()
{
	return nameOfWeapon;
}
int Weapon::getDamage()
{
	return damageFactor;
}
int Weapon::getBlast()
{
	return blastRadius;
}
int Weapon::getShotB()
{
	return shotBehavior;
}