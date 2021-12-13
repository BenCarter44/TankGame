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

using namespace std;


class GameContainer
{
private: // common game elements
	Style backgroundStyle;
	Style titleBackground;
	Style mainMenuBackground;
	Style selection;
	Style textBoxBackground;



	Rectangle2D background;
	Rectangle2D title;
	Rectangle2D mainMenu;

	KeyboardListener keys;
	KeyboardListener keys2;

	Console c;
	bool endGame;
	WindowScaler winX;
	WindowScaler winY;

	

	//friend bool HumanPlayer::aimMenu(GameContainer& gc);
	// player stuff

	Player* player1;
	Player* player2;

public:
	GameContainer();
	void startMenu();
	void newPlayerMenu();
	void loadPlayerMenu();
	void onlinePlayerMenu();
	bool isGameEnd();
	void arena();
	static void sleep(unsigned int l);


};
#endif
