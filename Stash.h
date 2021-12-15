/*

Stash class


By Benjamin Carter - December 14, 2021


This class stores information about a "stash" of weapons. This is the quantity and the type of weapon.

The stash object can get a weapon type, use one up, or get remaining in the stash.

This class is composed of the class weapon.

*/

#ifndef STASHH
#define STASHH
// a class/struct of weapon and number available. This is so you can get a nice vector of Stash

#include "Weapon.h"

class Stash
{
private:
	Weapon w;  // weapon and count
	int count;
public:
	Stash();
	Stash(Weapon w);
	Stash(Weapon w, int ct);   // constructors

	void init();
	void init(Weapon w);
	void init(Weapon w, int ct);  // init-type "constructors"

	Weapon getWeaponType();   // getters and methods
	Weapon useUpWeapon();  // use up a weapon in the stash, decreasing the count by 1
	int getRemaining();     // get remaining weapons
	void setAmount(int x);
	void increaseAmount(int x); 
	

};
#endif