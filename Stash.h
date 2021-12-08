#ifndef STASHH
#define STASHH
// a class/struct of weapon and number available. This is so you can get a nice vector of Stash

#include "Weapon.h"

class Stash
{
private:
	Weapon w;
	int count;
public:
	Stash();
	Stash(Weapon w);
	Stash(Weapon w, int ct);

	void init();
	void init(Weapon w);
	void init(Weapon w, int ct);

	Weapon getWeaponType();
	Weapon useUpWeapon();
	int getRemaining();
	void setAmount(int x);
	void increaseAmount(int x);
	

};
#endif