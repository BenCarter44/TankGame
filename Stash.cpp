#include "Stash.h"

Stash::Stash()
{
	init();
}
Stash::Stash(Weapon w)
{
	init(w);
}
Stash::Stash(Weapon w, int ct)
{
	init(w, ct);
}
void Stash::init()
{
	count = 0;
}
void Stash::init(Weapon w)
{
	this->w = w;
	count = 1;
}
void Stash::init(Weapon w, int ct)
{
	if (ct > 0)
	{
		this->w = w;
		count = ct;
	}
	else
	{
		this->w = w;
		count = 1;
	}
}

Weapon Stash::getWeaponType()
{
	return w;
}
Weapon Stash::useUpWeapon()
{
	count--;
	return w;
}
int Stash::getRemaining()
{
	return count;
}
void Stash::setAmount(int x)
{
	count = x;
}
void Stash::increaseAmount(int x)
{
	count += x;
}