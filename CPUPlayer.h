/*

CPUPlayer class


By Benjamin Carter - December 14, 2021

This class extends the Player class, specifically for a computer player.


This class contains a pointer to the opponent's tank.
This allows for it to aim accurately.

The CPUPlayer calculates the shot under the aimMenu method. 

The difficulty determines how far/close the shot will be to the opponent.

100 is far 1 is close. 



*/



#ifndef CPUPL
#define CPUPL

#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>


class CPUPlayer : public Player
{
private:
	Tank* otherTank; // pointer to the other tank
	Shot shotHold; // current shot
	int difficulty = 1; // 100(easy) to 1(hard);

public:
	CPUPlayer();  // constructors
	void init();
	CPUPlayer(string name); 
	void init(string name);

	void saveOtherTank(Tank* t);  // setter

	Shot aimShot();  // return the current shot
	bool aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY); // aim the shot
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