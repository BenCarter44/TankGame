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

using namespace std;
using namespace std::chrono;

void newPlayer(Console& c);
void loadPlayer(Console& c);
void onlineGame(Console& c);
int main()
{
	/*********	    init         ******/
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	Console c = Console();

	if (!c.getSupport())
	{
		cout << "Console display does not support ASCII Escape Codes.\nExiting ";
		return 0;
	}

	cout << "Loading...\n";
	/**********************  Main Menu!   *************************/
	cout << "Please resize screen now to approporate size! Must be above 20x15";
	sleep_for(milliseconds(2000));
	c.init();
	if (c.getHeight() < 15 || c.getWidth() < 20)
	{
		cout << "\n Screen to small! Exiting!";
		return 0;
	}
	c.fillScreen();
	WindowScaler winX = WindowScaler(0, 100, 0, c.getWidth());
	WindowScaler winY = WindowScaler(0, 30, 0, c.getHeight());


	// Background!
	Rectangle2D background = Rectangle2D(0, 0, c.getWidth(), c.getHeight());
	Style backgroundStyle;
	backgroundStyle.setBackgroundColor(20, 20, 20);
	backgroundStyle.setTextColor(20, 255, 20);

	background.setFill(backgroundStyle);
	c.addShape(&background);

	// Menu Window. Will have a banner at the top and a selection box.

	Rectangle2D title = Rectangle2D(winX.getVal(25), 2, winX.getVal(50), 4);
	Style titleBackground;
	titleBackground.setBackgroundColor(0, 0, 255);
	titleBackground.setTextColor(255, 255, 255);
	title.setFill(titleBackground);
	c.addShape(&title);

	// Bottom menu window

	Rectangle2D mainMenu = Rectangle2D(winX.getVal(25), 7, winX.getVal(50), c.getHeight() - 3 - 7);
	Style mainMenuBackground;
	mainMenuBackground.setBackgroundColor(255, 0, 255);
	mainMenuBackground.setTextColor(255, 255, 255);
	mainMenuBackground.turnOffBlink();
	mainMenu.setFill(mainMenuBackground);
	c.addShape(&mainMenu);

	// text
	c.putString("Tank Game! V1 ", winX.getVal(27), 3);
	c.putString("By Benjamin Carter ", winX.getVal(28), 4);


	string options[] = {
		"Start as a new player",
		"Load player",
		"Sign into online arena",
		"Exit"
	};

	for (int x = 0; x < 4; x++)
	{
		string tx = to_string(x + 1) + " - " + options[x];
		c.putString(tx, winX.getVal(27), 8 + x);
	}
	c.setTitle("Tank Game V1");
	c.render();

	/******************** MENU SELECTION ******************/
	KeyboardListener keys = KeyboardListener(140);
#ifndef LINUX
	keys.addKey(VK_UP);
	keys.addKey(VK_DOWN);
	keys.addKey(VK_LEFT);
	keys.addKey(VK_RIGHT);
	keys.addKey(VK_RETURN);

	Style selection;
	selection.setBackgroundColor(50, 50, 50);
	selection.setTextColor(255, 0, 0);
	int cursor = 8;
	int oldCursor = 8;
	bool newData = true;
	int out = 0;
	while (true)
	{
		keys.listen();
		unsigned char charIn = keys.getKey();

		if (newData)
		{
			Rectangle2D itemOld = Rectangle2D(winX.getVal(25), oldCursor, winX.getVal(50), 1);
			Rectangle2D itemCurrent = Rectangle2D(winX.getVal(25), cursor, winX.getVal(50), 1);


			itemCurrent.setFill(selection);
			itemOld.setFill(mainMenuBackground);
			c.addShape(&itemOld);
			c.addShape(&itemCurrent);
			c.putString(to_string(cursor - 8 + 1) + " - " + options[cursor - 8], winX.getVal(27), cursor);
			c.putString(to_string(oldCursor - 8 + 1) + " - " + options[oldCursor - 8], winX.getVal(27), oldCursor);
			c.smartRender();
			newData = false;
		}
		if (charIn == VK_UP)
		{
			oldCursor = cursor;
			cursor--;
			newData = true;
		}
		else if (charIn == VK_DOWN)
		{
			oldCursor = cursor;
			cursor++;
			newData = true;
		}
		else if (charIn == VK_RETURN)
		{
			out = cursor - 8;
			break;
		}
		if (cursor < 8)
		{
			cursor = 4 + 8 - 1;
		}
		else if (cursor >= (8 + 4))
		{
			cursor = 8;
		}
		sleep_for(milliseconds(25)); // 40fps 

	}
	// returns out - the number that the user selected. 
#endif
	
	if (out == 0)
	{
		// start as new player
		newPlayer(c);
	}
	else if (out == 1)
	{
		loadPlayer(c);
		// load player
	}
	else if (out == 2)
	{
		onlineGame(c);
		// sign into online arena
	}
	else if (out == 3)
	{
		c.clear();
		Rectangle2D background = Rectangle2D(0, 0, c.getWidth(), c.getHeight());
		Style backgroundStyle;
		backgroundStyle.setBackgroundColor(20, 20, 20);
		backgroundStyle.setTextColor(20, 255, 20);

		background.setFill(backgroundStyle);
		c.addShape(&background);
		c.render();
		return 0;
	}
	
	return 0;
}
void newPlayer(Console& c)
{
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	WindowScaler winX = WindowScaler(0, 100, 0, c.getWidth());
	WindowScaler winY = WindowScaler(0, 30, 0, c.getHeight());


	// Menu Window. Will have a banner at the top and a selection box.

	// Bottom menu window
	Rectangle2D backFill = Rectangle2D(winX.getVal(25), 7, winX.getVal(50), c.getHeight() - 7);
	Style backgroundStyle;
	backgroundStyle.setBackgroundColor(20, 20, 20);
	backgroundStyle.setTextColor(20, 255, 20);

	backFill.setFill(backgroundStyle);
	c.addShape(&backFill);


	Rectangle2D mainMenu = Rectangle2D(winX.getVal(25), 7, winX.getVal(50), 6);
	Style mainMenuBackground;
	mainMenuBackground.setBackgroundColor(255, 0, 255);
	mainMenuBackground.setTextColor(255, 255, 255);
	mainMenuBackground.turnOffBlink();
	mainMenu.setFill(mainMenuBackground);
	c.addShape(&mainMenu);

	Rectangle2D textBox = Rectangle2D(winX.getVal(26), 10, winX.getVal(48), 1);
	Style textBoxBackground;
	textBoxBackground.setBackgroundColor(150, 150, 150);
	textBoxBackground.setTextColor(255, 255, 255);
	textBox.setFill(textBoxBackground);
	c.addShape(&textBox);

	
	// text
	c.putString("Welcome new player! ", winX.getVal(27), 8);
	c.putString("What is your name? ", winX.getVal(28), 9);
	c.smartRender();

	KeyboardListener keys = KeyboardListener(150);
	keys.addKey('A');
	keys.addKey('B');
	keys.addKey('C');
	keys.addKey('D');
	keys.addKey('E');
	keys.addKey('F');
	keys.addKey('G');
	keys.addKey('H');
	keys.addKey('I');
	keys.addKey('J');
	keys.addKey('K');
	keys.addKey('L');
	keys.addKey('M');
	keys.addKey('N');
	keys.addKey('O');
	keys.addKey('P');
	keys.addKey('Q');
	keys.addKey('R');
	keys.addKey('S');
	keys.addKey('T');
	keys.addKey('U');
	keys.addKey('V');
	keys.addKey('W');
	keys.addKey('X');
	keys.addKey('Y');
	keys.addKey('Z');
	keys.addKey(VK_RETURN);
	keys.addKey(VK_BACK);
	keys.addKey(VK_CAPITAL);

	string playerName = "";
	bool capital = true;
	while (true)
	{
		keys.listen();
		unsigned char inc = keys.getKey();
		if (inc != 0)
		{
			if (inc == VK_RETURN && playerName.size() != 0)
			{
				break;
			}
			else if(inc == VK_BACK)
			{
				if (playerName.size() > 0)
				{
					playerName = playerName.substr(0, playerName.size() - 1);
				}
			}
			else if (inc == VK_CAPITAL)
			{
				capital = !capital;
			}
			else
			{
				if (playerName.size() < 30 && inc != VK_RETURN )
				{
					if (capital)
					{
						playerName += inc;
					}
					else
					{
						playerName += tolower(inc);
					}
				}
			}
			string dump = "";
			for (int x = 0; x < winX.getVal(48); x++)
			{
				dump = dump + ' ';
			}
			c.putString(dump,winX.getVal(26), 10);
			c.putString(playerName, winX.getVal(26), 10);
			c.smartRender();
		}
		sleep_for(milliseconds(25));
	}
	cout << playerName.size();
	// what is the name? Set key presses. 
}
void loadPlayer(Console& c)
{
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	WindowScaler winX = WindowScaler(0, 100, 0, c.getWidth());
	WindowScaler winY = WindowScaler(0, 30, 0, c.getHeight());


	// Background!
	Rectangle2D background = Rectangle2D(0, 0, c.getWidth(), c.getHeight());
	Style backgroundStyle;
	backgroundStyle.setBackgroundColor(20, 20, 20);
	backgroundStyle.setTextColor(20, 255, 20);

	background.setFill(backgroundStyle);
	c.addShape(&background);

	// Menu Window. Will have a banner at the top and a selection box.

	Rectangle2D title = Rectangle2D(winX.getVal(25), 2, winX.getVal(50), 4);
	Style titleBackground;
	titleBackground.setBackgroundColor(0, 0, 255);
	titleBackground.setTextColor(255, 255, 255);
	title.setFill(titleBackground);
	c.addShape(&title);

	// Bottom menu window

	Rectangle2D mainMenu = Rectangle2D(winX.getVal(25), 7, winX.getVal(50), c.getHeight() - 3 - 7);
	Style mainMenuBackground;
	mainMenuBackground.setBackgroundColor(255, 0, 255);
	mainMenuBackground.setTextColor(255, 255, 255);
	mainMenuBackground.turnOffBlink();
	mainMenu.setFill(mainMenuBackground);
	c.addShape(&mainMenu);

	// text
	c.putString("What player to load? ", winX.getVal(27), 3);
	c.putString("By Benjamin Carter ", winX.getVal(28), 4);
	c.smartRender();
	sleep_for(milliseconds(1000));
}
void onlineGame(Console& c)
{
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	WindowScaler winX = WindowScaler(0, 100, 0, c.getWidth());
	WindowScaler winY = WindowScaler(0, 30, 0, c.getHeight());


	// Background!
	Rectangle2D background = Rectangle2D(0, 0, c.getWidth(), c.getHeight());
	Style backgroundStyle;
	backgroundStyle.setBackgroundColor(20, 20, 20);
	backgroundStyle.setTextColor(20, 255, 20);

	background.setFill(backgroundStyle);
	c.addShape(&background);

	// Menu Window. Will have a banner at the top and a selection box.

	Rectangle2D title = Rectangle2D(winX.getVal(25), 2, winX.getVal(50), 4);
	Style titleBackground;
	titleBackground.setBackgroundColor(0, 0, 255);
	titleBackground.setTextColor(255, 255, 255);
	title.setFill(titleBackground);
	c.addShape(&title);

	// Bottom menu window

	Rectangle2D mainMenu = Rectangle2D(winX.getVal(25), 7, winX.getVal(50), c.getHeight() - 3 - 7);
	Style mainMenuBackground;
	mainMenuBackground.setBackgroundColor(255, 0, 255);
	mainMenuBackground.setTextColor(255, 255, 255);
	mainMenuBackground.turnOffBlink();
	mainMenu.setFill(mainMenuBackground);
	c.addShape(&mainMenu);

	// text
	c.putString("Please sign in ", winX.getVal(27), 3);
	c.putString("Username:", winX.getVal(28), 4);
	c.smartRender();
	sleep_for(milliseconds(1000));
}

	/*cout << "Getting IP of current network" << endl;
	cpr::Response r = cpr::Get(cpr::Url{"https://codingcando.com/api/getIP"});
	cout << "Current IP: " << r.text << endl;

	r = cpr::Get(cpr::Url{ "https://codingcando.com/api/getIPInfo?ip=" + r.text });
	cout << "Information: " << r.text << endl;
	cout << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << endl;

	sleep_for(milliseconds(500));
	cout << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << endl;
	*/
/*
#ifndef LINUX
	k.addKey(VK_UP);
	k.addKey(VK_DOWN);
	k.addKey(VK_LEFT);
	k.addKey(VK_RIGHT);
	k.addKey('A');
	k.addKey('B');
	k.addKey('C');
	k.addKey('D');
	k.addKey('E');
	k.addKey('F');
	k.addKey('G');
	k.addKey('H');
	k.addKey('I');
	k.addKey('J');
	k.addKey('K');
	k.addKey('L');
	k.addKey('M');
	k.addKey('N');
	k.addKey('O');
	k.addKey('P');
	k.addKey('Q');
	k.addKey('R');
	k.addKey('S');
	k.addKey('T');
	k.addKey('U');
	k.addKey('V');
	k.addKey('W');
	k.addKey('X');
	k.addKey('Y');
	k.addKey('Z');


	int x = 0;
	int y = 0;
	Style sp = Style();
	sp.setBackgroundColor(0, 255, 0);
	Style off = Style();
	off.setBackgroundColor(0, 0, 0);
	bool newData = 0;
	int oldX = 0;
	int oldY = 0;
	while (true)
	{
		k.listen();

		unsigned char charIn = k.getKey();
		if (newData)
		{
			oldX = x;
			oldY = y;
		}
		newData = false;
		if (charIn == VK_UP)
		{
			y = y - 1;
			newData = true;
		}
		else if (charIn == VK_DOWN)
		{
			y = y + 1;
			newData = true;
		}
		else if (charIn == VK_LEFT)
		{
			x = x - 1;
			newData = true;
		}
		else if (charIn == VK_RIGHT)
		{
			x = x + 1;
			newData = true;
		}
		if (newData)
		{
			Point2D p = Point2D(x, y);
			p.setFill(sp);
			Point2D old = Point2D(oldX, oldY);
			old.setFill(off);
			c.addShape(&p);
			c.addShape(&old);
			c.smartRender();
		}




	}
#endif
*/

