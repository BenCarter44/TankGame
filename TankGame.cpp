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
#include "FileSaver.h"

using namespace std;
using namespace std::chrono;

int main()
{
	
	/*
	FileSaver fs("tankTest.txt");
	
	Player* ben = new CPUPlayer("Ben");
	Player* joe = new CPUPlayer("Joe");

	Weapon pebble = Weapon("Pebbles", 1, 1);
	Stash st2 = Stash(pebble, 200);
	ben->setMoney(1000);
	ben->addWeaponStash(st2);

	joe->addWeaponStash(st2);
	joe->setDifficulty(90);
	ben->setDifficulty(1);
	fs.storePlayer(ben, joe);
	ben->setName("Jake");
	fs.saveFile();
	
	fs.loadFile();
	cout << fs.isBad();
	
	
	*/
	
	
	GameContainer game = GameContainer();
	if (game.isGameEnd())
	{
		return 0;
	}
	game.startMenu();
	//game.arena();

	/*

	



	
	*/
	

	return 0;
}