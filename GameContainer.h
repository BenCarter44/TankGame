/*

GameContainer class


By Benjamin Carter - December 14, 2021

This class contains the main parts of the program!!

Each section of the game has its own method.

In the constructor, similar styles and shapes are stored to be used throughout the game. 

The newPlayerMenu() deals with the query of the new player's name

The loadPlayerMenu() obtains which player to load the data from.

The onlinePlayerMenu() is saved for the future.

The mainMenuScreen() is the main selection screen, where the user can select to go to the arena or the shop

The arena() displays the arena
The shop() displays the shop


All the displaying is through the Console object of c. Console is the main class of the PrettyConsole project. See TankGame.h for more info.
WindowScaler is used to create a grid on where to display everything.

The players are polymorhic variables of the player class. This allows them to be a CPUPlayer or a HumanPlayer

See GameContainer.cpp for more
*/

#ifndef GAMECONT
#define GAMECONT


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
#include "HumanPlayer.h"
#include "CPUPlayer.h"
#include "PStruct.h"
#include "Ground.h"
#include "FileSaver.h"

using namespace std;


class GameContainer
{
private: // common game elements
	Style backgroundStyle;
	Style titleBackground;
	Style mainMenuBackground;
	Style mainMenuSubStyle;  
	Style selection;
	Style textBoxBackground;



	Rectangle2D background;
	Rectangle2D title;
	Rectangle2D mainMenu;
	Rectangle2D mainMenuSub;

	KeyboardListener keys;
	KeyboardListener keys2;

	Console c; // the console handler
	bool endGame;
	WindowScaler winX;
	WindowScaler winY;  // scale handlers

	

	// player stuff

	Player* player1;
	Player* player2;  // the player pointers 
	void printLabelArena();
	void newPlayerMenu();
	void loadPlayerMenu();
	void onlinePlayerMenu();    // each feature of the game
	void mainMenuScreen();
	
	void arena();
	void shop();
public:
	GameContainer(); // the constructor
	void startMenu();  // the menu, and game end
	bool isGameEnd();
	static void sleep(unsigned int l); // a static sleep. This allows for delay in the game


};
#endif
