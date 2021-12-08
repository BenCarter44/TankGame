// TankGame.cpp : Defines the entry point for the application.
//


/*
Contain a store
Contain ability to save player progress. (store on server, or load from file) 

Player data:
   - strength of tank
   - bought items
   - money
   

Follow the progression of ideas in a storyboard. Storyboard the game

Come up with the requirements of the game. Some screenshots

Make the game easy/simple. Then add things to it. Your storyboard will be your "contract". Your game will be graded against your storyboard


Must have inheritance and a polymorphic variable.

Must submit a UML with project!


Video:
Where is the inheritance?
Where is the polymorphic variable?
Where is the composition?


*/



#include "TankGame.h"
#include "PrettyConsole/console.h"
#include "PrettyConsole/point.h"
#include "PrettyConsole/Rectangle.h"
#include "PrettyConsole/Line.h"
#include "PrettyConsole/styles.h"

#include <iostream>
#include "cpr/cpr.h"
#include "KeyboardListener.h"
#include "WindowScaler.h"
#include "GameContainer.h"
#include "HumanPlayer.h"
#include "CPUPlayer.h"

using namespace std;
using namespace std::chrono;

int main()
{
	/*GameContainer game = GameContainer();
	if (game.isGameEnd())
	{
		return 0;
	}
	game.startMenu();
	*/

	HumanPlayer hp = HumanPlayer("Ben");
	CPUPlayer cpuPlayer = CPUPlayer("Computer");

	Weapon w = Weapon("Gun", 5);

	hp.addWeaponStash(Stash(w, 15));
	hp.displayAll();

	Tank* t = cpuPlayer.getTank();
	t->takeDamage(w.getDamage());

	cpuPlayer.displayAll();
	


	return 0;
}