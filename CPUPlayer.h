#ifndef CPUPL
#define CPUPL

#include "Player.h"

class CPUPlayer : public Player
{
private:
	Tank* otherTank;

public:
	CPUPlayer();
	void init();
	CPUPlayer(string name);
	void init(string name);

	void saveOtherTank(Tank* t);

	Shot aimShot();
	bool aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY)
	{
		return false;
	}

};



#endif