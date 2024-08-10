/*

HumanPlayer class


By Benjamin Carter - December 14, 2021

This class extends the Player class, specifically for a human player. 


This contains the menu where the player makes the selection of the power, weapon, and angle. 


*/

#ifndef HUMANPL
#define HUMANPL

#include "Player.h"
#include "PrettyConsole/console.h"
#include "PrettyConsole/inputHandler.h"
#include "WindowScaler.h"
#include "GameContainer.h"
#include <vector>
#include <string>
using namespace std;

class HumanPlayer : public Player
{
private:
	int oldPower;
	int oldAngle;   // power and angle of the previous shot
	Stash* oldWeapon;  // the stash of the weapons
	bool isQuitB = false; // if the user selected "Quit"
public:
	HumanPlayer();
	void init();
	HumanPlayer(string name);
	void init(string name);
	
	Shot aimShot();  // aim the shot, return a shot object
	bool aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY);  // display the meny
	void saveOtherTank(Tank* t)
	{
		return; // a do nothing method required by the super class
	}
	void setDifficulty(int df)   // these three methods are just here to fuffill the requirement for the Player abstract class. They don't actually do anything.
	{
		return; // a do nothing method required by the super class
	}
	int getDifficulty()
	{
		return 0; 	// a do nothing method required by the super class
	}
	bool isQuit()
	{
		return isQuitB;  // getter
	}
};



#endif
