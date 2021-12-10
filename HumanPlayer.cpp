#include "HumanPlayer.h"



HumanPlayer::HumanPlayer() : Player()
{
	isCPU = false;
}
HumanPlayer::HumanPlayer(string name) : Player(name)
{
	isCPU = false;
}
void HumanPlayer::init()
{
	Player::init();
	isCPU = false;
}
void HumanPlayer::init(string name)
{
	Player::init(name);
	isCPU = false;
}


Shot HumanPlayer::aimShot()
{
	return Shot();
}
