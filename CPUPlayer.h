#ifndef CPUPL
#define CPUPL

#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

class CPUPlayer : public Player
{
private:
	Tank* otherTank;
	Shot shotHold;
	int difficulty = 1; // 100(easy) to 1(hard);

public:
	CPUPlayer();
	void init();
	CPUPlayer(string name);
	void init(string name);

	void saveOtherTank(Tank* t);

	Shot aimShot();
	bool aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY);
	void setDifficulty(int df)
	{
		difficulty = df;
	}
	int getDifficulty()
	{
		return difficulty;
	}
	bool isQuit()
	{
		return false;
	}
};



#endif