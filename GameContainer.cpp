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


*/
#include "GameContainer.h"

GameContainer::GameContainer()
{
	// setup game globals
	
	endGame = !c.getSupport();  // see if the computer supports PrettyConsole
	cout << "Please resize screen now to approporate size! Must be above 40x21";
	
	sleep(5000);
	c.init();
	endGame = endGame || (c.getHeight() < 21 || c.getWidth() < 40);

	winX.init(0, 100, 0, c.getWidth());
	winY.init(50, 0, 0, c.getHeight());



	// players
	HumanPlayer* ben = new HumanPlayer("Ben"); // default player 1
	CPUPlayer* joe = new CPUPlayer("Joe");     // default player 2

	Weapon pebble = Weapon("Pebbles", 1, 1);
	Stash st2 = Stash(pebble, 200);
	ben->setMoney(150);
	ben->addWeaponStash(st2);

	joe->addWeaponStash(st2);
	joe->setDifficulty(100);
	player1 = ben;
	player2 = joe;   // setup the pretend players (will be overwritten)



	// keys
	keys.setPauseTime(150);
	keys2.setPauseTime(150);

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
	keys2.addKey('J');  // setup the keyboard listeners
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
	backgroundStyle.setBackgroundColor(35, 96, 0);  // setup the styles
	backgroundStyle.setTextColor(20, 255, 20);

	titleBackground.setBackgroundColor(168, 84, 0);
	titleBackground.setTextColor(255, 255, 0);

	mainMenuBackground.setBackgroundColor(175, 171, 171);
	mainMenuBackground.setTextColor(0, 0, 0);
	mainMenuBackground.turnOffBlink();

	selection.setBackgroundColor(150, 150, 255);
	selection.setTextColor(255, 255, 0);

	textBoxBackground.setBackgroundColor(150, 150, 150);
	textBoxBackground.setTextColor(255, 255, 255);

	mainMenuSubStyle.setBackgroundColor(50, 50, 50);

	// shapes
	background.init(0, 0, c.getWidth(), c.getHeight());
	title.init(winX.getVal(25), 2, winX.getVal(50), 9);
	mainMenu.init(winX.getVal(25),12, winX.getVal(50), c.getHeight() - 5 -11);
	mainMenuSub.init(winX.getVal(25)+2, 12+1, winX.getVal(50), c.getHeight() - 5 - 11);
	// patches
	background.setFill(backgroundStyle);
	title.setFill(titleBackground);
	mainMenu.setFill(mainMenuBackground);
	mainMenuSub.setFill(mainMenuSubStyle);

}
void GameContainer::startMenu()
{
	c.fillScreen();  // add the shapes
	// Background!
	c.addShape(&background);
	// Menu Window. Will have a banner at the top and a selection box.	
	c.addShape(&title);
	// Bottom menu window
	c.addShape(&mainMenuSub);
	c.addShape(&mainMenu);

	// text
	string fancyTitle[] =
	{
		"  _______          _       _____                       __      _____  ",
		" |__   __|        | |     / ____|                      \\ \\    / /__ \\ ",
		"    | | __ _ _ __ | | __ | |  __  __ _ _ __ ___   ___   \\ \\  / /   ) |",
		"    | |/ _` | '_ \\| |/ / | | |_ |/ _` | '_ ` _ \\ / _ \\   \\ \\/ /   / / ",
		"    | | (_| | | | |   <  | |__| | (_| | | | | | |  __/    \\  /   / /_ ",
		"    |_|\\__,_|_| |_|_|\\_\\  \\_____|\\__,_|_| |_| |_|\\___|     \\/   |____|"
	};

	for (int x = 0; x < 6; x++)
	{
		c.putString(fancyTitle[x], winX.getVal(27), 3+x);
		
	}
	c.putString("By Benjamin Carter ", winX.getVal(28), 4+6);
	  // display the titles
	string options[] = {
		"Start as a new player",
		"Load player",
		"Sign into online arena",
		"Exit"
	};

	for (int x = 0; x < 4; x++)
	{
		string tx = to_string(x + 1) + " - " + options[x];
		c.putString(tx, winX.getVal(27), 13 + x);
	}
	c.setTitle("Tank Game V2 - Benjamin Carter");
	c.render();


	
	// get user input

	int cursor = 13;
	int oldCursor = 13;
	bool newData = true;
	int out = 0;
#ifndef LINUX
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
			c.putString(to_string(cursor - 13 + 1) + " - " + options[cursor - 13], winX.getVal(27), cursor);
			c.putString(to_string(oldCursor - 13 + 1) + " - " + options[oldCursor - 13], winX.getVal(27), oldCursor);
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
			out = cursor - 13;
			break;
		}
		if (cursor < 13)
		{
			cursor = 4 + 13 - 1;
		}
		else if (cursor >= (13 + 4))
		{
			cursor = 13;
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
void GameContainer::mainMenuScreen()
{
	c.fillScreen();
	// Background!
	c.addShape(&background);
	// Menu Window. Will have a banner at the top and a selection box.	
	c.addShape(&title);
	// Bottom menu window
	c.addShape(&mainMenuSub);
	c.addShape(&mainMenu);

	// text
	

	

	string fancyTitle[] =
	{
		"  _______          _       _____                       __      _____  ",
		" |__   __|        | |     / ____|                      \\ \\    / /__ \\ ",
		"    | | __ _ _ __ | | __ | |  __  __ _ _ __ ___   ___   \\ \\  / /   ) |",
		"    | |/ _` | '_ \\| |/ / | | |_ |/ _` | '_ ` _ \\ / _ \\   \\ \\/ /   / / ",
		"    | | (_| | | | |   <  | |__| | (_| | | | | | |  __/    \\  /   / /_ ",
		"    |_|\\__,_|_| |_|_|\\_\\  \\_____|\\__,_|_| |_| |_|\\___|     \\/   |____|"
	};

	for (int x = 0; x < 6; x++)
	{
		c.putString(fancyTitle[x], winX.getVal(27), 3 + x);

	}
	c.putString("By Benjamin Carter ", winX.getVal(28), 4 + 6);
	c.putString("Welcome " + player1->getName() + "!", winX.getVal(55), 4 + 6);


	// text



	string options[] = {
		"Enter Match",
		"Visit the shop",
		"Save Game",
		"Save and Exit",
		"Exit without saving"
	};

	for (int x = 0; x < 5; x++)
	{
		string tx = to_string(x + 1) + " - " + options[x];
		c.putString(tx, winX.getVal(27), 13 + x);
	}
	c.render();



	// get user input
	sleep(100);
	int cursor = 13;
	int oldCursor = 13;
	bool newData = true;
	int out = 0;
#ifndef LINUX
	while (true)
	{
		keys.listen();
		unsigned char 
			charIn = keys.getKey();

		if (newData)
		{
			Rectangle2D itemOld = Rectangle2D(winX.getVal(25), oldCursor, winX.getLength(50), 1);
			Rectangle2D itemCurrent = Rectangle2D(winX.getVal(25), cursor, winX.getLength(50), 1);


			itemCurrent.setFill(selection);
			itemOld.setFill(mainMenuBackground);
			c.addShape(&itemOld);
			c.addShape(&itemCurrent);
			c.putString(to_string(cursor - 13 + 1) + " - " + options[cursor - 13], winX.getVal(27), cursor);
			c.putString(to_string(oldCursor - 13 + 1) + " - " + options[oldCursor - 13], winX.getVal(27), oldCursor);
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
			out = cursor - 13;
			break;
		}
		if (cursor < 13)
		{
			cursor = 5 + 13 - 1;
		}
		else if (cursor >= (13 + 5))
		{
			cursor = 13;
		}
		sleep(25); // 40fps 

	}
	// returns out - the number that the user selected. 
#endif
	sleep(100);
	if (out == 0)
	{
		// start as new player
		arena();
	}
	else if (out == 1)
	{
		shop();
	}
	else if (out == 2)
	{
	//	c.clear();
	//	c.addShape(&background);

		FileSaver fs("tankTest.txt");
		fs.loadFile();
		if (fs.isBad())
		{
			c.putString("Failed to save game!", 0, 0);
			c.render();
			sleep(2000);
			mainMenuScreen();
		}
		else
		{
			fs.storePlayer(player1, player2);
			fs.saveFile();
			Rectangle2D* dialogBox = new Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));
			Style dialogBoxIn;
			Style dialogBoxOut;

			dialogBoxIn.init(mainMenuBackground);
			dialogBoxOut.init(mainMenuSubStyle);

			//dialogBoxIn.setBackgroundColor(127, 127, 127);
			//dialogBoxOut.setBackgroundColor(80, 80, 80);
			dialogBoxIn.setTextColor(255, 255, 200);
			dialogBox->setFill(dialogBoxIn);
			dialogBox->setBorder(dialogBoxOut);

			c.addShape(dialogBox);
			c.putString("Saved game!", winX.getVal(35), winY.getVal(34));
			c.smartRender();
			sleep(2000);
			mainMenuScreen();
		}

		
	}
	else if (out == 3)
	{
	//	c.clear();
	//	c.addShape(&background);

		FileSaver fs("tankTest.txt");
		fs.loadFile();
		if (fs.isBad())
		{
			Rectangle2D* dialogBox = new Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));
			Style dialogBoxIn;
			Style dialogBoxOut;

			dialogBoxIn.init(mainMenuBackground);
			dialogBoxOut.init(mainMenuSubStyle);

			//dialogBoxIn.setBackgroundColor(127, 127, 127);
			//dialogBoxOut.setBackgroundColor(80, 80, 80);
			dialogBoxIn.setTextColor(255, 255, 200);
			dialogBox->setFill(dialogBoxIn);
			dialogBox->setBorder(dialogBoxOut);

			c.addShape(dialogBox);
			c.putString("Failed to save game!", winX.getVal(35), winY.getVal(34));
			c.smartRender();
			sleep(2000);
			mainMenuScreen();
		}
		else
		{
			fs.storePlayer(player1, player2);
			fs.saveFile();
			Rectangle2D* dialogBox = new Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));
			Style dialogBoxIn;
			Style dialogBoxOut;

			dialogBoxIn.init(mainMenuBackground);
			dialogBoxOut.init(mainMenuSubStyle);

			//dialogBoxIn.setBackgroundColor(127, 127, 127);
			//dialogBoxOut.setBackgroundColor(80, 80, 80);
			dialogBoxIn.setTextColor(255, 255, 200);
			dialogBox->setFill(dialogBoxIn);
			dialogBox->setBorder(dialogBoxOut);

			c.addShape(dialogBox);
			c.putString("Saved game!", winX.getVal(35), winY.getVal(34));
			c.smartRender();
			sleep(2000);
			c.clear();
			c.addShape(&background);
			c.render();
			endGame = true;
		}
		
	}
	else if (out == 4)
	{
		c.clear();
		c.addShape(&background);
		c.render();
		endGame = true;
	}

	endGame = true;
}
void GameContainer::shop()
{
	c.fillScreen();
	// Background!
	c.addShape(&background);
	// Menu Window. Will have a banner at the top and a selection box.	
	


	// background box
	Rectangle2D* back1 = new Rectangle2D(winX.getVal(6), winY.getVal(42), winX.getLength(89), winY.getLength(36));
	Rectangle2D* back3 = new Rectangle2D(winX.getVal(5), winY.getVal(43), winX.getLength(89), winY.getLength(36));
	Rectangle2D* back2 = new Rectangle2D(winX.getVal(3), winY.getVal(47), winX.getLength(20), winY.getLength(5));
	Rectangle2D* back4 = new Rectangle2D(winX.getVal(7), winY.getVal(38), winX.getLength(38), winY.getLength(29));
	Rectangle2D* highlight1 = new Rectangle2D(winX.getVal(7), winY.getVal(42), winX.getLength(32), winY.getLength(2));
	Rectangle2D* highlight2 = new Rectangle2D(winX.getVal(8), winY.getVal(36), winX.getLength(35), 1);
	Rectangle2D* highlight3 = new Rectangle2D(winX.getVal(83), winY.getVal(44), winX.getLength(9), 1);

	Rectangle2D* highlight4 = new Rectangle2D(winX.getVal(51), winY.getVal(42), winX.getLength(9), 1);


	// styles
	

	
	
	
	back1->setFill(mainMenuSubStyle);
	back2->setFill(titleBackground);

	Style topInfo;
	topInfo.setTextColor(0, 0, 0);
	topInfo.setBackgroundColor(169, 253, 221);

	back3->setFill(mainMenuBackground);


	Style s4;
	s4.setBackgroundColor(214,220,229);
	back4->setFill(s4);


	Style selCopy;
	selCopy.setBackgroundColor(189, 189, 255);
	selCopy.setTextColor(20, 0, 255);
	
	highlight2->setFill(selCopy);
	//highlight2->setFill


	
	highlight1->setFill(topInfo);


	Style quitSty;
	quitSty.setBackgroundColor(248, 176, 174);
	quitSty.setTextColor(255, 0, 0);

	highlight3->setFill(quitSty);


	
	Style s8;
	s8.setBackgroundColor(2);
	highlight4->setFill(titleBackground);

	c.addShape(back1);
	c.addShape(back2);
	c.addShape(back3);
	c.addShape(back4);
	c.addShape(highlight1);
	c.addShape(highlight2);
	c.addShape(highlight3);
	c.addShape(highlight4);

//	cout << '\n';
//	cout << player1->getMoney();
//	return;
	c.putString("Store", winX.getVal(51), winY.getVal(42));
	c.putString("Tank Game!", winX.getVal(4), winY.getVal(46));
	c.putString("By Benjamin Carter", winX.getVal(4), winY.getVal(46)+1);
	c.putString("You have $" + to_string(player1->getMoney()), winX.getVal(7), winY.getVal(42));
	int percent = (player1->getTank()->getHP() * 100) / player1->getTank()->getMaxHP();
	c.putString("Your tank has currrently " + to_string(player1->getTank()->getHP()) + " out of " + to_string(player1->getTank()->getMaxHP()) + "hp - " + to_string(percent) + "% left", winX.getVal(7), winY.getVal(41));
	c.putString("Your current stash: ", winX.getVal(8), winY.getVal(36));
	c.putString("Press Q to quit ", winX.getVal(83)+1, winY.getVal(44));




	Weapon* weapons = new Weapon[10];
	weapons[0].init("Pebbles", 1, 1);
	weapons[1].init("Rock", 3, 1);
	weapons[2].init("Small Shot", 10, 1);
	weapons[3].init("Bomb",25, 1);
	weapons[4].init("Light Rocket", 50, 1);
	weapons[5].init("Big Shot", 60, 1);
	weapons[6].init("Heavy Rocket",75, 1);
	weapons[7].init("Standard Missle", 120, 1);
	weapons[8].init("Jumbo Missle",250, 1);
	weapons[9].init("Nuke", 750, 1);


	// display each weapon
	bool color = false;
	unsigned char allSelections[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };
	int costs[] = { 1,10,1,2,15,40,50,80,120,180,250,1000 };

	costs[0] = player1->getTank()->getMaxHP() - player1->getTank()->getHP();
	costs[0] = costs[0];

	for (int x = 0; x < 12; x++)  // for each weapon, display them
	{
		Rectangle2D* r = new Rectangle2D(winX.getVal(52 + 11 * (x % 3)), winY.getVal(40 - 7 * (x / 3)), winX.getLength(11), winY.getLength(6));
		Style sty;
		sty.setTextColor(0);
		if (color)
		{
			sty.setBackgroundColor(187,253,198);
		}
		else
		{
			sty.setBackgroundColor(188,249,252);
		}
		r->setFill(sty);
		color = !color;
		c.addShape(r);

		if (x == 0)
		{
			c.putString("Repair tank",winX.getVal(53), winY.getVal(39));
			c.putString("Cost: $" + to_string(costs[x]), winX.getVal(54), winY.getVal(37));
			c.putString("Press " + string(1,allSelections[x]) + " to buy", winX.getVal(54), winY.getVal(36));
		}
		else if (x == 1)
		{
			c.putString("Add Armor", winX.getVal(53 + 11 * (x % 3)), winY.getVal(39 - 7 * (x / 3)));
			c.putString("Cost: $" + to_string(costs[x]), winX.getVal(54 + 11 * (x % 3)), winY.getVal(37 - 7 * (x / 3) ));
			c.putString("Press " + string(1, allSelections[x]) + " to buy", winX.getVal(54 + 11 * (x % 3)), winY.getVal(36 - 7 * (x / 3)));
		}
		else
		{
			//cout << x << '\n';
			c.putString("Buy: " + weapons[x - 2].getName(), winX.getVal(53 + 11 * (x % 3)), winY.getVal(39 - 7 * (x / 3)));
			c.putString("Damage: " + to_string(weapons[x - 2].getDamage()), winX.getVal(53 + 11 * (x % 3)), winY.getVal(38 - 7 * (x / 3)));
			c.putString("Cost: $" + to_string(costs[x]), winX.getVal(54 + 11 * (x % 3)), winY.getVal(37 - 7 * (x / 3)));
			c.putString("Press " + string(1, allSelections[x]) + " to buy", winX.getVal(54 + 11 * (x % 3)), winY.getVal(36 - 7 * (x / 3)));
		}
		
		//sleep(50);

		delete r;
	}
	c.smartRender();
	vector<Stash*> myStash = player1->getWeapons();


	for (int x = 0; x < myStash.size(); x++)
	{
		string out = myStash[x]->getWeaponType().getName() + " damage of " + to_string(myStash[x]->getWeaponType().getDamage()) + " - Remaining: " + to_string(myStash[x]->getRemaining());
		c.putString(out, winX.getVal(9), winY.getVal(35) + x);
		
		c.smartRender();
		//sleep(50);

	}

	KeyboardListener ky(120);

	for (int x = 0; x < 12; x++)
	{
		ky.addKey(allSelections[x]);
	}
	ky.addKey('Q');
	bool done = false;
	unsigned char inc = 0;
	int selection = 0;
	while (!done)
	{
		ky.listen();
		inc = ky.getKey();
		for (int x = 0; x < 12; x++)
		{
			if (allSelections[x] == inc)
			{
				selection = x;
				done = true;
				break;
			}
		}
		if (inc == 'Q')
		{
			mainMenuScreen();
			return;
		}
	}
	if (selection == 0)  // the prompt code - repair
	{
		// repair!
		Rectangle2D* dialogBox = new Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));


		// styles

		Style dialogBoxIn;
		Style dialogBoxOut;

		dialogBoxIn.init(mainMenuBackground);
		dialogBoxOut.init(mainMenuSubStyle);

		//dialogBoxIn.setBackgroundColor(127, 127, 127);
		//dialogBoxOut.setBackgroundColor(80, 80, 80);
		dialogBoxIn.setTextColor(255, 255, 200);
		dialogBox->setFill(dialogBoxIn);
		dialogBox->setBorder(dialogBoxOut);



		c.addShape(dialogBox);
		

		int money = player1->getMoney();
		if (costs[0] <= money)
		{

			c.putString("Repair tank for " + to_string(costs[0]), winX.getVal(35), winY.getVal(35));
			c.putString("Yes - (Y) or No (N)", winX.getVal(35), winY.getVal(34));
			c.smartRender();

			KeyboardListener subKey(150);
			subKey.addKey('Y');
			subKey.addKey('N');
			subKey.addKey('Q');
			while (true)
			{
				subKey.listen();
				unsigned char inc = subKey.getKey();
				if (inc == 'Y')
				{
					player1->getTank()->repair();
					player1->pay(costs[0]);
					
					mainMenuScreen();
					break;
				}
				else if(inc == 'N' || inc == 'Q')
				{
					shop();
					break;
				}
			}
		}

		else
		{
			c.putString("Not enough funds!", winX.getVal(35), winY.getVal(35));
			c.smartRender();
			sleep(2000);
		}

	}
	else if (selection == 1) // the prompt code - armor
	{
		// armor!
		Rectangle2D* dialogBox = new Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(6));


		// styles

		Style dialogBoxIn;
		Style dialogBoxOut;

		dialogBoxIn.init(mainMenuBackground);
		dialogBoxOut.init(mainMenuSubStyle);

		//dialogBoxIn.setBackgroundColor(127, 127, 127);
		//dialogBoxOut.setBackgroundColor(80, 80, 80);
		dialogBoxIn.setTextColor(255, 255, 200);
		dialogBox->setFill(dialogBoxIn);
		dialogBox->setBorder(dialogBoxOut);



		c.addShape(dialogBox);


		int money = player1->getMoney();
		int quantity = 0;
		

		c.putString("Add armor (1 hit point) for " + to_string(costs[1]), winX.getVal(35), winY.getVal(35));
		c.putString("Quantity to order: " + to_string(quantity),winX.getVal(35), winY.getVal(34));
		c.putString("Total Cost: " + to_string(quantity * costs[selection]), winX.getVal(35), winY.getVal(33));
		c.putString("Enter to order or (Q) to quit", winX.getVal(35), winY.getVal(32));
		c.smartRender();
#ifndef LINUX



		KeyboardListener subKey(150);
		subKey.addKey(VK_UP);
		subKey.addKey(VK_DOWN);
		subKey.addKey('Q');
		subKey.addKey(VK_RETURN);
		
		while (true)
		{
			subKey.listen();
			unsigned char inc = subKey.getKey();
			if (inc == VK_RETURN)
			{
				if (costs[1] * quantity <= money)
				{
					player1->getTank()->setMaxHP(player1->getTank()->getMaxHP() + quantity);
					player1->pay(costs[1] * quantity);
					mainMenuScreen();
					break;
				}
				else
				{
					c.addShape(dialogBox);
					c.putString("Not enough funds!", winX.getVal(35), winY.getVal(35));
					c.smartRender();
					sleep(2000);
					shop();
					break;
				}
			}
			else if (inc == 'Q')
			{
				shop();
				break;
			}
			else if (inc == VK_UP)
			{
				quantity++;
				c.putString("Quantity to order: " + to_string(quantity) + "  ", winX.getVal(35), winY.getVal(34));
				c.putString("Total Cost: " + to_string(quantity * costs[selection]) + "  ", winX.getVal(35), winY.getVal(33));
				c.smartRender();
			}
			else if (inc == VK_DOWN)
			{
				quantity--;
				c.putString("Quantity to order: " + to_string(quantity) + "  ", winX.getVal(35), winY.getVal(34));
				c.putString("Total Cost: " + to_string(quantity * costs[selection]) + "  ", winX.getVal(35), winY.getVal(33));
				c.smartRender();
			}
		}
#endif // !LINUX
	
	}
	else if (selection > 1) // the prompt code, any other weapon
	{
		// weapons
		Rectangle2D* dialogBox = new Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(6));


		// styles

		Style dialogBoxIn;
		Style dialogBoxOut;

		dialogBoxIn.init(mainMenuBackground);
		dialogBoxOut.init(mainMenuSubStyle);

		//dialogBoxIn.setBackgroundColor(127, 127, 127);
		//dialogBoxOut.setBackgroundColor(80, 80, 80);
		dialogBoxIn.setTextColor(255, 255, 200);
		dialogBox->setFill(dialogBoxIn);
		dialogBox->setBorder(dialogBoxOut);

		
		
		c.addShape(dialogBox);



		int money = player1->getMoney();
		int quantity = 0;

		Weapon wep = weapons[selection - 2];
		c.putString("Buy " + wep.getName() + " with " + to_string(wep.getDamage()) + "pt damage", winX.getVal(35), winY.getVal(35));
		c.putString("Quantity to order: " + to_string(quantity), winX.getVal(35), winY.getVal(34));
		c.putString("Total Cost: " + to_string(quantity * costs[selection]), winX.getVal(35), winY.getVal(33));
		c.putString("Enter to order or (Q) to quit", winX.getVal(35), winY.getVal(32));
		c.smartRender();
#ifndef LINUX
		KeyboardListener subKey(150);
		subKey.addKey(VK_UP);
		subKey.addKey(VK_DOWN);
		subKey.addKey('Q');
		subKey.addKey(VK_RETURN);

		while (true)
		{
			subKey.listen();
			unsigned char inc = subKey.getKey();
			if (inc == VK_RETURN)
			{
				if (costs[selection] * quantity <= money)
				{
					Stash newStash = Stash(wep, quantity);
					player1->addWeaponStash(newStash);
					player1->pay(costs[selection] * quantity);
					mainMenuScreen();
					break;
				}
				else
				{
					c.addShape(dialogBox);
					c.putString("Not enough funds!", winX.getVal(35), winY.getVal(35));
					c.smartRender();
					sleep(2000);
					shop();
					break;
				}
			}
			else if (inc == 'Q')
			{
				shop();
				break;
			}
			else if (inc == VK_UP)
			{
				quantity++;
				c.putString("Quantity to order: " + to_string(quantity) + "  ", winX.getVal(35), winY.getVal(34));
				c.putString("Total Cost: " + to_string(quantity * costs[selection]) + "  ", winX.getVal(35), winY.getVal(33));
				c.smartRender();
			}
			else if (inc == VK_DOWN)
			{
				if (quantity > 0)
				{
					quantity--;
				}
				c.putString("Quantity to order: " + to_string(quantity) + "  ", winX.getVal(35), winY.getVal(34));
				c.putString("Total Cost: " + to_string(quantity * costs[selection]) + "  ", winX.getVal(35), winY.getVal(33));
				c.smartRender();
			}
		}
#endif
	}
	
	// pop up window. Ask user for amount or exit.
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

	//Rectangle2D mainMenu = Rectangle2D(winX.getVal(25), 7, winX.getLength(50), 6);
	
	//mainMenu.setFill(mainMenuBackground);
	c.addShape(&mainMenuSub);
	c.addShape(&mainMenu);

	Rectangle2D textBox = Rectangle2D(winX.getVal(26), 15, winX.getLength(48), 1);	
	textBox.setFill(textBoxBackground);

	c.addShape(&textBox);

	string fancyTitle[] =
	{
		"  _______          _       _____                       __      _____  ",
		" |__   __|        | |     / ____|                      \\ \\    / /__ \\ ",
		"    | | __ _ _ __ | | __ | |  __  __ _ _ __ ___   ___   \\ \\  / /   ) |",
		"    | |/ _` | '_ \\| |/ / | | |_ |/ _` | '_ ` _ \\ / _ \\   \\ \\/ /   / / ",
		"    | | (_| | | | |   <  | |__| | (_| | | | | | |  __/    \\  /   / /_ ",
		"    |_|\\__,_|_| |_|_|\\_\\  \\_____|\\__,_|_| |_| |_|\\___|     \\/   |____|"
	};

	for (int x = 0; x < 6; x++)
	{
		c.putString(fancyTitle[x], winX.getVal(27), 3 + x);

	}
	c.putString("By Benjamin Carter ", winX.getVal(28), 4 + 6);

	
	// text
	c.putString("Welcome new player! ", winX.getVal(27), 13);
	c.putString("What is your name? ", winX.getVal(28), 14);
	c.render();

	

	string playerName = "";
	bool capital = true;
#ifndef LINUX

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
			c.putString(dump, winX.getVal(26), 15);
			c.putString(playerName, winX.getVal(26), 15);
			c.smartRender();
		}
		sleep(25);
	}
	int o = player1->getMoney();
	player1->init(playerName);
	player1->setMoney(o);
	player2->init("CPU");
	player2->setDifficulty(100);

	Weapon pebble = Weapon("Pebbles", 1, 1);
	Stash st2 = Stash(pebble, 2000);
	player2->addWeaponStash(st2);
#endif
	mainMenuScreen();

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
	c.addShape(&mainMenuSub);
	c.addShape(&mainMenu);

	Rectangle2D textBox = Rectangle2D(winX.getVal(26), 14, winX.getLength(48), 1);
	textBox.setFill(textBoxBackground);

	c.addShape(&textBox);

	string fancyTitle[] =
	{
		"  _______          _       _____                       __      _____  ",
		" |__   __|        | |     / ____|                      \\ \\    / /__ \\ ",
		"    | | __ _ _ __ | | __ | |  __  __ _ _ __ ___   ___   \\ \\  / /   ) |",
		"    | |/ _` | '_ \\| |/ / | | |_ |/ _` | '_ ` _ \\ / _ \\   \\ \\/ /   / / ",
		"    | | (_| | | | |   <  | |__| | (_| | | | | | |  __/    \\  /   / /_ ",
		"    |_|\\__,_|_| |_|_|\\_\\  \\_____|\\__,_|_| |_| |_|\\___|     \\/   |____|"
	};

	for (int x = 0; x < 6; x++)
	{
		c.putString(fancyTitle[x], winX.getVal(27), 3 + x);

	}
	c.putString("By Benjamin Carter ", winX.getVal(28), 4 + 6);


	// text


	c.putString("Pick a player to load:", winX.getVal(27), 14);
	
	
	FileSaver fs("tankTest.txt");
	
	fs.loadFile();
	if (fs.isBad())
	{
		c.putString("Bad File!", 0, 0);
		c.smartRender();
		sleep(2000);
		endGame = true;
		return;
	}
	vector<string> options = fs.getPlayerNames();




	int optionSize = options.size();


	for (int x = 0; x < optionSize; x++)
	{
		//cout << options[x] << endl;
		string tx = to_string(x + 1) + " - " + options[x];
		c.putString(tx, winX.getVal(27), 16 + x);
	}
	//return;
	c.smartRender();

#ifndef LINUX

	// get user input

	int cursor = 16;
	int oldCursor = 16;
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
			c.putString(to_string(cursor - 16 + 1) + " - " + options[cursor - 16], winX.getVal(27), cursor);
			c.putString(to_string(oldCursor - 16 + 1) + " - " + options[oldCursor - 16], winX.getVal(27), oldCursor);
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
			out = cursor - 16;
			break;
		}
		if (cursor < 16)
		{
			cursor = optionSize + 16 - 1;
		}
		else if (cursor >= (16 + optionSize))
		{
			cursor = 16;
		}
		sleep(25); // 40fps 

	}
	// returns out - the number that the user selected. 
	player1 = fs.getPlayer(options[out]);
	player2 = fs.getOtherPlayer(options[out]);
#endif


	

	mainMenuScreen();
	
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
#ifndef LINUX

	using namespace std::chrono;
	using namespace std::this_thread;
	sleep_for(milliseconds(l));
#endif // !LINUX
}
void GameContainer::printLabelArena()
{
	string player1Name = player1->getName();
	string player2Name = player2->getName();

	Tank* tankPlayer1 = player1->getTank();
	Tank* tankPlayer2 = player2->getTank();
	c.putString("Tank Arena!", winX.getVal(45), winY.getVal(48));
	c.putString(player1Name + " vs. " + player2Name, winX.getVal(44), winY.getVal(47));
	

	c.putString(player1Name, winX.getVal(2), winY.getVal(48));

	int health = tankPlayer1->getHP();
	int maxHealth = tankPlayer1->getMaxHP();
	int percent = (health * 100) / maxHealth;
	c.putString("Health: " + to_string(health) + "/" + to_string(maxHealth) + "  (" + to_string(percent) + "%)  ", winX.getVal(3), winY.getVal(46));

	int money = player1->getMoney();
	c.putString("Dollars: $" + to_string(money), winX.getVal(3), winY.getVal(45));


	c.putString(player2Name, winX.getVal(99) - player2Name.length() - 1, winY.getVal(48));

	health = tankPlayer2->getHP();
	maxHealth = tankPlayer2->getMaxHP();
	percent = (health * 100) / maxHealth;
	string outString = "  Health: " + to_string(health) + "/" + to_string(maxHealth) + "  (" + to_string(percent) + "%)  ";
	c.putString(outString, winX.getVal(99) - outString.length()-2, winY.getVal(46));
}
void GameContainer::arena()
{

	// player stuff
	player2->getTank()->repair();
	// make the tank a little harder
		// make the CPUPlayer harder
	if (player2->getDifficulty() > 5)
	{
		player2->setDifficulty(player2->getDifficulty() - 1);
	}
	else
	{
		
		vector<Stash*> theWeapons = player2->getWeapons();
		int x = theWeapons.size();
		int last = 0;
		if (x != 0)
		{
			last = theWeapons[x-1]->getWeaponType().getDamage();
		}
		int f = 0;
		if (last + 10 > last * 1.5)
		{
			f = last + 10;
		}
		else
		{
			f = last * 1.5;
		}
		Weapon q = Weapon("Wep" + to_string(x), f);

		Stash newWeaponSet = Stash(q, 150);
		player2->addWeaponStash(newWeaponSet);

	}
	

	
	// get player info
	string player1Name = player1->getName();
	string player2Name = player2->getName();

	Tank* tankPlayer1 = player1->getTank();
	Tank* tankPlayer2 = player2->getTank();
	int volley = 1;



	// set up shapes

	Rectangle2D* usernameStatusBoxL = new Rectangle2D(winX.getVal(1), winY.getVal(48), winX.getLength(15), winY.getLength(4));
	Rectangle2D* usernameStatusBoxR = new Rectangle2D(winX.getVal(84), winY.getVal(48), winX.getLength(15), winY.getLength(4));
	
	Rectangle2D* titleBox = new Rectangle2D(winX.getVal(41), winY.getVal(48), winX.getLength(18), winY.getLength(2));
	Rectangle2D* volleyTicker = new Rectangle2D(winX.getVal(44), winY.getVal(46), winX.getLength(12), 1);
	Rectangle2D* turnMarker = new Rectangle2D(winX.getVal(1), winY.getVal(43), winX.getVal(8), 1);

	
	Rectangle2D* dialogBox = new Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));
	

	// styles
	
	Rectangle2D background;
	background.init(0, 0, c.getWidth(), c.getHeight());


	Style backCopy;
	backCopy.init(backgroundStyle);
	backCopy.setBackgroundColor(20, 20, 20);

	background.setFill(backCopy);

	
	//Style usernameBox;
	//usernameBox.setBackgroundColor(187, 253, 198);
	//usernameBox.setTextColor(255, 255, 220);

	Style tickerStyle;
	tickerStyle.setBackgroundColor(35, 96, 0);
	tickerStyle.setTextColor(0, 255, 0);

	Style dialogBoxIn;
	Style dialogBoxOut;

	dialogBoxIn.init(mainMenuBackground);
	dialogBoxOut.init(mainMenuSubStyle);

	//dialogBoxIn.setBackgroundColor(127, 127, 127);
	//dialogBoxOut.setBackgroundColor(80, 80, 80);
	dialogBoxIn.setTextColor(255, 255, 200);
	dialogBox->setFill(dialogBoxIn);
	dialogBox->setBorder(dialogBoxOut);

	usernameStatusBoxL->setFill(mainMenuBackground);
	usernameStatusBoxR->setFill(mainMenuBackground);
	titleBox->setFill(titleBackground);
	volleyTicker->setFill(tickerStyle);
	//turnMarker->setFill(tickerStyle);

	



	// add shapes
	c.clear();
	c.addShape(&background);
	c.addShape(usernameStatusBoxL);
	c.addShape(usernameStatusBoxR);
	c.addShape(titleBox);
	c.addShape(volleyTicker);
	//c.addShape(&turnMarker);
	c.addShape(dialogBox);

	// put in text

	printLabelArena();
	c.putString("Volley: " + to_string(volley) + " of 10", winX.getVal(45), winY.getVal(46));


	//c.putString(to_string(player2->getDifficulty()), 0, 0);

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
	tankStyle.setBackgroundColor(0, 0, 255);
	tank1.setFill(tankStyle);
	c.addShape(&tank1);

	player1->setTank(3, winY.reverse(c.getHeight() - totalHeights[winX.getVal(4)] - winY.getLength(2)));


	Rectangle2D tank2 = Rectangle2D(winX.getVal(93), c.getHeight() - totalHeights[winX.getVal(93)] - winY.getLength(2), winX.getLength(4), winY.getLength(2));

	tank2.setFill(titleBackground);
	c.addShape(&tank2);

	player2->setTank(93, winY.reverse(c.getHeight() - totalHeights[winX.getVal(93)] - winY.getLength(2)));


	///c.putString(to_string(c.getWidth()) + " " + to_string(c.getHeight()), 0, 0);

	c.render(); // render is faster when the whole screen is to be written.

	
	int damageP1 = player1->getTank()->getHP();
	int damageP2 = player1->getTank()->getHP();
	bool turn = true; // true if player 1
	while (volley < 11)
	{
		Player* shootingPlayer;
		Player* defensePlayer;

		if (turn)
		{
			shootingPlayer = player1;
			defensePlayer = player2;
		}
		else
		{
			shootingPlayer = player2;
			defensePlayer = player1;
		}
		
		if (turn)
		{

			turnMarker->init(winX.getVal(1), winY.getVal(43), winX.getVal(8), 1);
			turnMarker->setFill(tickerStyle);
			c.addShape(turnMarker);
			c.putString("Player1's turn", winX.getVal(2), winY.getVal(43));

			Rectangle2D turnMarker2 = Rectangle2D(winX.getVal(91), winY.getVal(43), winX.getVal(8), 1);
			turnMarker2.setFill(backCopy);
			c.addShape(&turnMarker2);

			c.putString("              ", winX.getVal(92), winY.getVal(43));
			
		}
		else
		{
			turnMarker->init(winX.getVal(91), winY.getVal(43), winX.getVal(8), 1);
			turnMarker->setFill(tickerStyle);
			c.addShape(turnMarker);

			Rectangle2D turnMarker2 = Rectangle2D(winX.getVal(1), winY.getVal(43), winX.getVal(8), 1);
			turnMarker2.setFill(backCopy);
			c.addShape(&turnMarker2);

			turnMarker->init(winX.getVal(91), winY.getVal(43), winX.getVal(8), 1);
			c.putString("Player2's turn", winX.getVal(92), winY.getVal(43));
			turnMarker->init(winX.getVal(1), winY.getVal(43), winX.getVal(8), 1);
			c.putString("              ", winX.getVal(2), winY.getVal(43));
		}
	
		
		
		bool out = false;
		if (shootingPlayer->isCPUPlayer()) // is shooting player CPU
		{
			shootingPlayer->saveOtherTank(defensePlayer->getTank());
		}
		else
		{
			c.addShape(dialogBox);
		}
		out = shootingPlayer->aimMenu(c, winX, winY);
		bool isQuit = shootingPlayer->isQuit();
		if (isQuit)
		{
			break;
		}
		
		c.smartRender();
		if (out) // if they can shoot a valid shot
		{
			Shot myShot = shootingPlayer->aimShot();
		//	c.putString(to_string((int)myShot.getAngle()) + "  ", 10, 0);
		//	c.putString(to_string((int)(myShot.getPower()*10) / 10.0) + "  ", 15, 0);
			myShot.calculatePoints();
			Rectangle2D dialogBoxBlackout = Rectangle2D(winX.getVal(33), winY.getVal(36), winX.getLength(17 * 2), winY.getLength(5));
			dialogBoxBlackout.setFill(backCopy);
			c.addShape(&dialogBoxBlackout);


			vector<PStruct> pts = myShot.getPoints();
			// draw the shot
			Style weaponStyle;
			weaponStyle.setBackgroundColor(255, 255, 0);
			Point2D actualPoint;

			Style oldStyle;
			int oldX = 0;
			int oldY = 0;
			unsigned char oldChar = ' ';
			for (int pointNumber = 0; pointNumber < pts.size(); pointNumber++)
			{
				// cout << (int)pts[pointNumber].x << " " << (int)pts[pointNumber].y << '\n';
				if (pts[pointNumber].x >= 0 && pts[pointNumber].x < winX.getInMax() && pts[pointNumber].y > 0 && pts[pointNumber].y < winY.getInMin())
				{
					actualPoint.init((int)winX.getDoubleVal(pts[pointNumber].x), (int)winY.getDoubleVal(pts[pointNumber].y));

					actualPoint.setFill(weaponStyle);
					if (!groundHandler.isGround(actualPoint.getAnchorX(), actualPoint.getAnchorY()))
					{
						if (oldX != 0 || oldY != 0)
						{
							Point2D oldP = Point2D(oldX, oldY);

							oldP.setFill(oldStyle);
							oldP.putChar(oldChar);
							c.addShape(&oldP);
						}
						oldX = actualPoint.getAnchorX();
						oldY = actualPoint.getAnchorY();
						oldStyle.init(c.getSpecificStyle(oldX, oldY));
						oldChar = c.getSpecificChar(oldX, oldY);


						c.addShape(&actualPoint);
					}
					else
					{
						break;
						//oldX = 0;
						//oldY = 0;
					}
					Tank* opponentTank = defensePlayer->getTank();

					if (pts[pointNumber].x >= opponentTank->getX() && pts[pointNumber].x <= opponentTank->getX() + 4 && pts[pointNumber].y >= opponentTank->getY() && pts[pointNumber].y <= opponentTank->getY() + 2)
					{
						// collision!!!!

						opponentTank->takeDamage(myShot.getWeapon().getDamage());
						shootingPlayer->earnMoney(myShot.getWeapon().getDamage());
						if (opponentTank->getHP() <= 0)
						{
							volley = 100;
						}
						break;
					}
						
					c.smartRender();
					sleep(1);
				}
				else if (pts[pointNumber].y >= winY.getInMin())
				{
					 // pass
				}
				else
				{
					break;
					//	cout << "BAD: " << winX.getVal(pts[pointNumber]->getAnchorX()) << " " << winY.getVal(pts[pointNumber]->getAnchorY()) << '\n';
				}
				
				
			}

			Point2D oldP = Point2D(oldX, oldY);

			oldP.setFill(oldStyle);
			oldP.putChar(oldChar);
			c.addShape(&oldP);
		}
		
		else
		{
			if (!shootingPlayer->isCPUPlayer())
			{
				c.addShape(dialogBox);
				string out = "You have no weapons remaining!";
				c.putString(out, winX.getVal(35), winY.getVal(35));
				c.smartRender();
				sleep(2000);
			}
		}

		printLabelArena();
		c.putString("Volley: " + to_string(volley) + " of 10", winX.getVal(45), winY.getVal(46));
		c.smartRender();
		if (turn)
		{
			volley++;
		}
		turn = !turn;
	}

	if (damageP1 - player1->getTank()->getHP() < damageP2 - player2->getTank()->getHP())
	{
		// win!
		//int winning = ((damageP2 - player2->getTank()->getHP()) * (damageP2 - player2->getTank()->getHP())) - ((damageP1 - player1->getTank()->getHP()) * (damageP1 - player1->getTank()->getHP()));
		int winning = ((damageP2 - player2->getTank()->getHP())) - (damageP1 - player1->getTank()->getHP());
		c.addShape(dialogBox);
		string out = "Game over!";
		c.putString(out, winX.getVal(35), winY.getVal(35));
		out = "You won the match. You receive $" + to_string(winning);
		c.putString(out, winX.getVal(35), winY.getVal(34));
		c.smartRender();
		player1->earnMoney(winning);
		sleep(2000);

	}
	else if(damageP1 - player1->getTank()->getHP() > damageP2 - player2->getTank()->getHP())
	{
		int winning = ((damageP2 - player2->getTank()->getHP())) - (damageP1 - player1->getTank()->getHP());
		c.addShape(dialogBox);
		string out = "Game over!";
		c.putString(out, winX.getVal(35), winY.getVal(35));
		out = "Soory, you lost the match.";
		c.putString(out, winX.getVal(35), winY.getVal(34));
		c.smartRender();
		player2->earnMoney(winning);
		sleep(2000);
	}
	else
	{
		c.addShape(dialogBox);
		string out = "Game over!";
		c.putString(out, winX.getVal(35), winY.getVal(35));
		out = "It's a tie!";
		c.putString(out, winX.getVal(35), winY.getVal(34));
		c.smartRender();
		sleep(2000);

	}
	


	



	mainMenuScreen();
	

}