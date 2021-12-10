#include "CPUPlayer.h"


CPUPlayer::CPUPlayer() : Player()
{
	isCPU = true;
}
CPUPlayer::CPUPlayer(string name) : Player(name)
{
	isCPU = true;
}
void CPUPlayer::init()
{
	Player::init();
	isCPU = true;
}
void CPUPlayer::init(string name)
{
	Player::init(name);
	isCPU = true;
}

void CPUPlayer::saveOtherTank(Tank* t)
{
	otherTank = t;
}

Shot CPUPlayer::aimShot()
{
	return Shot();
}
