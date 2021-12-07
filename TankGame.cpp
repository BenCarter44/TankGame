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




*/



#include "TankGame.h"
#include "PrettyConsole/console.h"
#include "PrettyConsole/point.h"
#include "PrettyConsole/styles.h"

#include <iostream>
#include "cpr/cpr.h"
#include "KeyboardListener.h"

using namespace std;
using namespace std::chrono;

int main()
{
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;
	Console c = Console();
	cout << "Hello CMake." << endl;
	cout << c.getWidth() << endl;
	cout << c.getHeight() << endl;
	cout << c.getSupport() << endl;

	if (!c.getSupport())
	{
		cout << "Console display does not support ASCII Escape Codes.\nExiting ";
		return 0;
	}
	c.render();
	/*cout << "Getting IP of current network" << endl;
	cpr::Response r = cpr::Get(cpr::Url{"https://codingcando.com/api/getIP"});
	cout << "Current IP: " << r.text << endl;

	r = cpr::Get(cpr::Url{ "https://codingcando.com/api/getIPInfo?ip=" + r.text });
	cout << "Information: " << r.text << endl;
	cout << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << endl;

	sleep_for(milliseconds(500));
	cout << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << endl;
	*/
	KeyboardListener k = KeyboardListener(150);
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
#endif

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
	return 0;
}
