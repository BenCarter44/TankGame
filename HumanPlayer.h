#ifndef HUMANPL
#define HUMANPL

#include "Player.h"
#include "PrettyConsole/console.h"
#include "WindowScaler.h"
#include "KeyboardListener.h"
#include "GameContainer.h"
#include <vector>
#include <string>
using namespace std;

class HumanPlayer : public Player
{
private:
	int oldPower;
	int oldAngle;
	Stash* oldWeapon;
public:
	HumanPlayer();
	void init();
	HumanPlayer(string name);
	void init(string name);
	
	Shot aimShot();
	bool aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY);
	void saveOtherTank(Tank* t)
	{
		return; // a do nothing method required by the super class
	}
};



#endif
