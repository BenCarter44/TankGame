#include "Player.h"

Player::Player()
{
	playerName = "CPU";
	money = 0;
}
Player::Player(string name)
{
	playerName = name;
	isCPU = false;
	money = 0;
}
void Player::init()
{
	playerName = "CPU";
}
void Player::init(string name)
{
	playerName = name;
	isCPU = false;
	money = 0;
}

void Player::setName(string name)
{
	playerName = name;
}
Tank* Player::getTank()
{
	return &(tank);
}

int Player::getMoney()
{
	return money;
}

void Player::setMoney(int m)
{
	money = m;
}
void Player::pay(int p)
{
	money = money - p;
}
void Player::earnMoney(int p)
{
	money = money + p;
}

vector<Stash*> Player::getWeapons()
{
	// check to see if any are 0
	vector<Stash*> temp;
	for (int x = 0; x < weaponHold.size(); x++)
	{
		if (weaponHold[x]->getRemaining() > 0)
		{
			temp.push_back(weaponHold[x]);
		}
	}
	weaponHold = temp;
	return weaponHold;
}


void Player::setTank(int x, int y)
{
	tank.setX(x);
	tank.setY(y);
}
