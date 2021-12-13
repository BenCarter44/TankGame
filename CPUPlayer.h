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

public:
	CPUPlayer();
	void init();
	CPUPlayer(string name);
	void init(string name);

	void saveOtherTank(Tank* t);

	Shot aimShot();
	bool aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY);

};



#endif