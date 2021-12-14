#ifndef PLAYERC
#define PLAYERC


#include <string>
#include <vector>
#include <iostream>

#include "PrettyConsole/console.h"
#include "WindowScaler.h"

#include "Tank.h"
#include "Shot.h"
#include "Stash.h"

using namespace std;

class Player // this will be a super class. It will have 2 sub classes: HumanPlayer and CPUPlayer
{
private:
	string playerName;
	vector<Stash*> weaponHold;
	int money;

protected:
	bool isCPU = true;
	Tank tank;

public:
	Player();
	virtual void init();
	Player(string name);
	virtual void init(string name);
	string getName()
	{
		return playerName;
	}
	void setName(string name);

	Tank* getTank();
	
	int getMoney();
	void setMoney(int m);
	void earnMoney(int p);
	void pay(int p);

	vector<Stash*> getWeapons();

	virtual Shot aimShot() = 0; // the abstract method!
	virtual bool aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY) = 0; // the abstract method!

	void addWeaponStash(Stash& s)
	{
		Stash* newStash = new Stash(s.getWeaponType(), s.getRemaining());
		weaponHold.push_back(newStash); // create new obj
	}

	void displayAll()
	{
		cout << "\n" << tank.getHP() << "\n";
		for (int x = 0; x < weaponHold.size(); x++)
		{
			cout << "Q: " + to_string(weaponHold[x]->getRemaining()) + " " + weaponHold[x]->getWeaponType().getName() + " damages: " + to_string(weaponHold[x]->getWeaponType().getDamage()) << '\n';
		}
	}
	void setTank(int x, int y);
	bool isCPUPlayer()
	{
		return isCPU;
	}
	virtual void saveOtherTank(Tank* t) = 0;
	virtual void setDifficulty(int df) = 0;
	virtual int getDifficulty() = 0;

};
#endif