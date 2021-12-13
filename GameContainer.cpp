
#include "GameContainer.h"
GameContainer::GameContainer()
{
	// setup game globals
	
	endGame = !c.getSupport();
	cout << "Please resize screen now to approporate size! Must be above 40x21";
	sleep(5000);

	c.init();
	endGame = endGame || (c.getHeight() < 21 || c.getWidth() < 40);

	winX.init(0, 100, 0, c.getWidth());
	winY.init(50, 0, 0, c.getHeight());


	// keys
	keys.setPauseTime(150);
	keys2.setPauseTime(80);

#ifndef LINUX
	keys.addKey(VK_UP);
	keys.addKey(VK_DOWN);
	keys.addKey(VK_LEFT);
	keys.addKey(VK_RIGHT);
	keys.addKey(VK_RETURN);

	keys2.addKey('A');
	keys2.addKey('B');
	keys2.addKey('C');
	keys2.addKey('D');
	keys2.addKey('E');
	keys2.addKey('F');
	keys2.addKey('G');
	keys2.addKey('H');
	keys2.addKey('I');
	keys2.addKey('J');
	keys2.addKey('K');
	keys2.addKey('L');
	keys2.addKey('M');
	keys2.addKey('N');
	keys2.addKey('O');
	keys2.addKey('P');
	keys2.addKey('Q');
	keys2.addKey('R');
	keys2.addKey('S');
	keys2.addKey('T');
	keys2.addKey('U');
	keys2.addKey('V');
	keys2.addKey('W');
	keys2.addKey('X');
	keys2.addKey('Y');
	keys2.addKey('Z');
	keys2.addKey(VK_RETURN);
	keys2.addKey(VK_BACK);
	keys2.addKey(VK_CAPITAL);
#endif
	// styles
	backgroundStyle.setBackgroundColor(20, 20, 20);
	backgroundStyle.setTextColor(20, 255, 20);

	titleBackground.setBackgroundColor(0, 0, 255);
	titleBackground.setTextColor(255, 255, 255);

	mainMenuBackground.setBackgroundColor(255, 0, 255);
	mainMenuBackground.setTextColor(255, 255, 255);
	mainMenuBackground.turnOffBlink();

	selection.setBackgroundColor(50, 50, 50);
	selection.setTextColor(255, 0, 0);

	textBoxBackground.setBackgroundColor(150, 150, 150);
	textBoxBackground.setTextColor(255, 255, 255);

	// shapes
	background.init(0, 0, c.getWidth(), c.getHeight());
	title.init(winX.getVal(25), 2, winX.getVal(50), 4);
	mainMenu.init(winX.getVal(25), 7, winX.getVal(50), c.getHeight() - 3 - 7);

	// patches
	background.setFill(backgroundStyle);
	title.setFill(titleBackground);
	mainMenu.setFill(mainMenuBackground);

}
void GameContainer::startMenu()
{
	c.fillScreen();
	// Background!
	c.addShape(&background);
	// Menu Window. Will have a banner at the top and a selection box.	
	c.addShape(&title);
	// Bottom menu window
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

#ifndef LINUX
	
	// get user input

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
			Rectangle2D itemOld = Rectangle2D(winX.getVal(25), oldCursor, winX.getLength(50), 1);
			Rectangle2D itemCurrent = Rectangle2D(winX.getVal(25), cursor, winX.getLength(50), 1);


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
		sleep(25); // 40fps 

	}
	// returns out - the number that the user selected. 
#endif

	if (out == 0)
	{
		// start as new player
		newPlayerMenu();
	}
	else if (out == 1)
	{
		loadPlayerMenu();
		// load player
	}
	else if (out == 2)
	{
		onlinePlayerMenu();
		// sign into online arena
	}
	else if (out == 3)
	{
		c.clear();
		c.addShape(&background);
		c.render();
		endGame = true;
	}

	endGame = true;
}
void GameContainer::newPlayerMenu()
{

	c.fillScreen();
	// Background!
	c.addShape(&background);
	// Menu Window. Will have a banner at the top and a selection box.	
	c.addShape(&title);
	// Bottom menu window

	Rectangle2D mainMenu = Rectangle2D(winX.getVal(25), 7, winX.getLength(50), 6);
	
	mainMenu.setFill(mainMenuBackground);
	c.addShape(&mainMenu);

	Rectangle2D textBox = Rectangle2D(winX.getVal(26), 10, winX.getLength(48), 1);	
	textBox.setFill(textBoxBackground);
	c.addShape(&textBox);


	// text
	c.putString("Welcome new player! ", winX.getVal(27), 8);
	c.putString("What is your name? ", winX.getVal(28), 9);
	c.smartRender();

	

	string playerName = "";
	bool capital = true;
	while (true)
	{
		keys2.listen();
		unsigned char inc = keys2.getKey();
		if (inc != 0)
		{
			if (inc == VK_RETURN && playerName.size() != 0)
			{
				break;
			}
			else if (inc == VK_BACK)
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
				if (playerName.size() < 30 && inc != VK_RETURN)
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
			c.putString(dump, winX.getVal(26), 10);
			c.putString(playerName, winX.getVal(26), 10);
			c.smartRender();
		}
		sleep(25);
	}
	c.putString(playerName, 0, 0);
	c.smartRender();
	sleep(1000);
	endGame = true;

	// return player name as string playerName
}
void GameContainer::loadPlayerMenu()
{
	c.fillScreen();
	// Background!
	c.addShape(&background);
	// Menu Window. Will have a banner at the top and a selection box.	
	c.addShape(&title);
	// Bottom menu window
	c.addShape(&mainMenu);

	// text
	c.putString("Tank Game! V1 ", winX.getVal(27), 3);
	c.putString("By Benjamin Carter ", winX.getVal(28), 4);

	c.putString("Pick a player to load:", winX.getVal(27), 8);

	string options[] = {
		"Player 1",
		"Player 2",
		"Player 3",
		"Player 4"
	};

	int optionSize = 4;

	for (int x = 0; x < optionSize; x++)
	{
		string tx = to_string(x + 1) + " - " + options[x];
		c.putString(tx, winX.getVal(27), 9 + x);
	}
	c.smartRender();

#ifndef LINUX

	// get user input

	int cursor = 9;
	int oldCursor = 9;
	bool newData = true;
	int out = 0;
	while (true)
	{
		keys.listen();
		unsigned char charIn = keys.getKey();

		if (newData)
		{
			Rectangle2D itemOld = Rectangle2D(winX.getVal(25), oldCursor, winX.getLength(50), 1);
			Rectangle2D itemCurrent = Rectangle2D(winX.getVal(25), cursor, winX.getLength(50), 1);


			itemCurrent.setFill(selection);
			itemOld.setFill(mainMenuBackground);
			c.addShape(&itemOld);
			c.addShape(&itemCurrent);
			c.putString(to_string(cursor - 9 + 1) + " - " + options[cursor - 9], winX.getVal(27), cursor);
			c.putString(to_string(oldCursor - 9 + 1) + " - " + options[oldCursor - 9], winX.getVal(27), oldCursor);
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
			out = cursor - 9;
			break;
		}
		if (cursor < 9)
		{
			cursor = optionSize + 9 - 1;
		}
		else if (cursor >= (9 + optionSize))
		{
			cursor = 9;
		}
		sleep(25); // 40fps 

	}
	// returns out - the number that the user selected. 
#endif

	c.putString(options[out], 0, 0);
	c.smartRender();
	sleep(1000);
	endGame = true;
}
void GameContainer::onlinePlayerMenu()
{
	c.putString("Not implemented yet", 0, 0);
	c.smartRender();
	sleep(1000);
	startMenu();
}


/* HELPER FUNCTIONS */
bool GameContainer::isGameEnd()
{
	return endGame;
}
void GameContainer::sleep(unsigned int l)
{
	using namespace std::chrono;
	using namespace std::this_thread;
	sleep_for(milliseconds(l));
}
void GameContainer::arena()
{

	// player stuffpppp


	HumanPlayer ben = HumanPlayer("Ben");
	HumanPlayer joe = HumanPlayer("Joe");
	
	Weapon rock = Weapon("rock", 5, 1);
	Weapon pebble = Weapon("pebble", 1, 1);
	Stash st = Stash(rock,100);
	Stash st2 = Stash(pebble, 1000);

	ben.addWeaponStash(st);
	ben.addWeaponStash(st2);
	joe.addWeaponStash(st);
	joe.addWeaponStash(st2);

	string player1Name = ben.getName();
	string player2Name = joe.getName();

	Tank* tankPlayer1 = ben.getTank();
	Tank* tankPlayer2 = joe.getTank();
	int volley = 1;



	// set up shapes

	Rectangle2D usernameStatusBoxL = Rectangle2D(winX.getVal(1), winY.getVal(48), winX.getLength(15), winY.getLength(4));
	Rectangle2D usernameStatusBoxR = Rectangle2D(winX.getVal(84), winY.getVal(48), winX.getLength(15), winY.getLength(4));
	
	Rectangle2D titleBox = Rectangle2D(winX.getVal(41), winY.getVal(48), winX.getLength(18), winY.getLength(2));
	Rectangle2D volleyTicker = Rectangle2D(winX.getVal(44), winY.getVal(46), winX.getLength(12), 1);
	Rectangle2D turnMarker; // = Rectangle2D(winX.getVal(1), winY.getVal(43), winX.getVal(8), 1);

	Rectangle2D dialogBox = Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));
	

	// styles
	
	backgroundStyle.setTextColor(255, 255, 255);
	background.setFill(backgroundStyle);

	
	Style usernameBox;
	usernameBox.setBackgroundColor(0, 255, 255);

	Style tickerStyle;
	tickerStyle.setBackgroundColor(255, 127, 0);

	Style dialogBoxIn;
	Style dialogBoxOut;

	dialogBoxIn.setBackgroundColor(127, 127, 127);
	dialogBoxOut.setBackgroundColor(80, 80, 80);

	usernameStatusBoxL.setFill(usernameBox);
	usernameStatusBoxR.setFill(usernameBox);
	titleBox.setFill(titleBackground);
	volleyTicker.setFill(tickerStyle);
	turnMarker.setFill(tickerStyle);

	dialogBox.setFill(dialogBoxIn);
	dialogBox.setBorder(dialogBoxOut);
	

	// add shapes
	c.clear();
	c.addShape(&background);
	c.addShape(&usernameStatusBoxL);
	c.addShape(&usernameStatusBoxR);
	c.addShape(&titleBox);
	c.addShape(&volleyTicker);
	//c.addShape(&turnMarker);
	c.addShape(&dialogBox);

	// put in text

	c.putString("Tank Arena!", winX.getVal(41), winY.getVal(48));
	c.putString(player1Name + " vs. " + player2Name, winX.getVal(41), winY.getVal(47));
	c.putString("Volley: " + to_string(volley) + " of 10", winX.getVal(45), winY.getVal(46));

	c.putString(player1Name, winX.getVal(1), winY.getVal(48));

	int health = tankPlayer1->getHP();
	int maxHealth = tankPlayer1->getMaxHP();
	int percent = (health * 100) / maxHealth;
	c.putString("Health: " + to_string(health) + "/" + to_string(maxHealth) + "  (" + to_string(percent) + ")",winX.getVal(1),winY.getVal(46));
	
	int money = ben.getMoney();
	c.putString("Dollars: $" + to_string(money), winX.getVal(1), winY.getVal(45));


	c.putString(player2Name, winX.getVal(99)-player2Name.length(), winY.getVal(48));

	health = tankPlayer2->getHP();
	maxHealth = tankPlayer2->getMaxHP();
	percent = (health * 100) / maxHealth;
	string outString = "Health: " + to_string(health) + "/" + to_string(maxHealth) + "  (" + to_string(percent) + ")";
	c.putString(outString, winX.getVal(99)-outString.length(), winY.getVal(46));


	// ground
	Ground groundHandler = Ground(c.getWidth(), c.getHeight());

	groundHandler.groundRandomizer();

	Style groundStyle;
	Point2D groundPoint;
	int* totalHeights = new int[c.getWidth()];
	for (int x = 0; x < c.getWidth(); x++)
	{
		totalHeights[x] = 0;
	}
	for (int y = 0; y < c.getHeight(); y++)
	{
		for (int x = 0; x < c.getWidth(); x++)
		{
			//cout << winX.getVal(x) << " " << winY.getVal(y) << '\n';
			if (groundHandler.isGround(x, y))
			{
				groundStyle.setBackgroundColor(0, Console::mapValue(y, c.getHeight(), 0, 50, 190), 0);
				groundPoint.init(x, y);
				groundPoint.setFill(groundStyle);
				c.addShape(&groundPoint);
				totalHeights[x] += 1;
			}
		}
	}



	// tanks
	Rectangle2D tank1 = Rectangle2D(winX.getVal(3), c.getHeight() - totalHeights[winX.getVal(4)] - winY.getLength(2), winX.getLength(4), winY.getLength(2));
	Style tankStyle;
	tankStyle.setBackgroundColor(255, 255, 0);
	tank1.setFill(tankStyle);
	c.addShape(&tank1);

	ben.setTank(3, winY.reverse(c.getHeight() - totalHeights[winX.getVal(4)] - winY.getLength(2)));


	Rectangle2D tank2 = Rectangle2D(winX.getVal(93), c.getHeight() - totalHeights[winX.getVal(93)] - winY.getLength(2), winX.getLength(4), winY.getLength(2));

	tank2.setFill(tankStyle);
	c.addShape(&tank2);

	joe.setTank(93, winY.reverse(c.getHeight() - totalHeights[winX.getVal(93)] - winY.getLength(2)));


	///c.putString(to_string(c.getWidth()) + " " + to_string(c.getHeight()), 0, 0);

	c.render(); // render is faster when the whole screen is to be written.

	
	bool turn = true; // true if player 1
	while (volley < 11)
	{
		if (turn)
		{
			turnMarker.init(winX.getVal(1), winY.getVal(43), winX.getVal(8), 1);
			c.putString("Player1's turn", winX.getVal(2), winY.getVal(43));
		}
		else
		{
			turnMarker.init(winX.getVal(91), winY.getVal(43), winX.getVal(8), 1);
			c.putString("Player2's turn", winX.getVal(92), winY.getVal(43));
		}
		if (turn)
		{
			
			
			//Rectangle2D dialogBox = Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));

			//c.putString("Weapon (W): ", winX.getVal(35), winY.getVal(35));
			

			// get user input
			
			//volley++;
			bool out = ben.aimMenu(c,winX,winY);
			c.putString(to_string(out), 0, 0);
			c.smartRender();
			if (out)
			{
				Shot myShot = ben.aimShot();
				myShot.calculatePoints();
				vector<PStruct> pts = myShot.getPoints();
				 // draw the shot
				Style weaponStyle;
				weaponStyle.setBackgroundColor(255, 0, 0);
				Point2D actualPoint;

				for (int pointNumber = 0; pointNumber < pts.size(); pointNumber++)
				{
					// cout << (int)pts[pointNumber].x << " " << (int)pts[pointNumber].y << '\n';
					if (pts[pointNumber].x >= 0 && pts[pointNumber].x < winX.getInMax() && pts[pointNumber].y > 0 && pts[pointNumber].y < winY.getInMin())
					{

						actualPoint.init((int)winX.getDoubleVal(pts[pointNumber].x), (int)winY.getDoubleVal(pts[pointNumber].y));
						actualPoint.setFill(weaponStyle);
						if (!groundHandler.isGround(actualPoint.getAnchorX(), actualPoint.getAnchorY()))
						{
							c.addShape(&actualPoint);

						}
					}
					else
					{
						//	cout << "BAD: " << winX.getVal(pts[pointNumber]->getAnchorX()) << " " << winY.getVal(pts[pointNumber]->getAnchorY()) << '\n';
					}

				}
				c.smartRender();
			}
			turn = !turn;
		}
		else
		{
			//Rectangle2D dialogBox = Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));

			//c.putString("Weapon (W): ", winX.getVal(35), winY.getVal(35));


			// get user input
			//volley++;
			bool out = joe.aimMenu(c, winX, winY);
			c.putString(to_string(out), 0, 0);
			c.smartRender();
			if (out)
			{
				Shot myShot = joe.aimShot();
				myShot.calculatePoints();
				vector<PStruct> pts = myShot.getPoints();
				// draw the shot
				Style weaponStyle;
				weaponStyle.setBackgroundColor(255, 0, 0);
				Point2D actualPoint;

				for (int pointNumber = 0; pointNumber < pts.size(); pointNumber++)
				{
					// cout << (int)pts[pointNumber].x << " " << (int)pts[pointNumber].y << '\n';
					if (pts[pointNumber].x >= 0 && pts[pointNumber].x < winX.getInMax() && pts[pointNumber].y > 0 && pts[pointNumber].y < winY.getInMin())
					{

						actualPoint.init((int)winX.getDoubleVal(pts[pointNumber].x), (int)winY.getDoubleVal(pts[pointNumber].y));
						actualPoint.setFill(weaponStyle);
						if (!groundHandler.isGround(actualPoint.getAnchorX(), actualPoint.getAnchorY()))
						{
							c.addShape(&actualPoint);
						}
					}
					else
					{
						//	cout << "BAD: " << winX.getVal(pts[pointNumber]->getAnchorX()) << " " << winY.getVal(pts[pointNumber]->getAnchorY()) << '\n';
					}

				}
				c.smartRender();
			}
			turn = !turn;
		}
	}

	



	
	





	/*
	HumanPlayer hp = HumanPlayer("Ben");
	CPUPlayer cpuPlayer = CPUPlayer("Computer");

	Weapon w = Weapon("Gun", 5);

	hp.addWeaponStash(Stash(w, 15));
	hp.displayAll();

	Tank* t = cpuPlayer.getTank();
	t->takeDamage(w.getDamage());

	cpuPlayer.displayAll();
	*/

}