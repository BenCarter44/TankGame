﻿// TankGame.cpp : Defines the entry point for the application.
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
using namespace std;

int main()
{
	Console c = Console();
	cout << "Hello CMake." << endl;
	cout << c.getWidth() << endl;
	cout << c.getHeight() << endl;
	cout << c.getSupport() << endl;

	return 0;
}
