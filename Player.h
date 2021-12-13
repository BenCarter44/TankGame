#ifndef PLAYERC
#define PLAYERC


#include <string>
#include <vector>
#include <iostream>

#include "Tank.h"
#include "Shot.h"
#include "Stash.h"

using namespace std;

class Player // this will be a super class. It will have 2 sub classes: HumanPlayer and CPUPlayer
{
private:
	string playerName;
	vector<Stash> weaponHold;
	int money;

protected:
	bool isCPU = true;
	Tank tank;

public:
	Player();
	void init();
	Player(string name);
	void init(string name);
	string getName()
	{
		return playerName;
	}
	void setName(string name);

	Tank* getTank();
	
	int getMoney();
	void setMoney(int m);
	void pay(int p);

	vector<Stash> getWeapons();

	virtual Shot aimShot() = 0; // the abstract method!

	void addWeaponStash(Stash s)
	{
		weaponHold.push_back(s);
	}

	void displayAll()
	{
		cout << tank.getHP() << "\n";
		for (int x = 0; x < weaponHold.size(); x++)
		{
			cout << "Q: " + to_string(weaponHold[x].getRemaining()) + " " + weaponHold[x].getWeaponType().getName() + " damages: " + to_string(weaponHold[x].getWeaponType().getDamage()) << '\n';
		}
	}
	void setTank(int x, int y);


};
#endif