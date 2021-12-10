#include "Player.h"

Player::Player()
{
	playerName = "CPU";
}
Player::Player(string name)
{
	playerName = name;
	isCPU = false;
}
void Player::init()
{
	playerName = "CPU";
}
void Player::init(string name)
{
	playerName = name;
	isCPU = false;
}

void Player::setName(string name)
{
	playerName = name;
}
Tank* Player::getTank()
{
	return &(tank);
}
