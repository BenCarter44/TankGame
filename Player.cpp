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

vector<Stash> Player::getWeapons()
{
	return weaponHold;
}


void Player::setTank(int x, int y)
{
	tank.setX(x);
	tank.setY(y);
}
