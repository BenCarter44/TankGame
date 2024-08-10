/*

KeyboardListener class


By Benjamin Carter - December 14, 2021

This class stores keys to listen to in a vector of character

Then, the class can listen and push all pressed target keys onto the keyStack. The key stack is a stack of character
The time is also stored.


The pauseTime is the amount of delay in milliseconds required before the key is counted as being pressed twice.


This class only works on WINDOWS right now!
Later, will try to get it platform-independent.

*/
#ifndef KEYBOARD_LTN
#define KEYBOARD_LTN

using namespace std;
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>

#else
#include <sys/ioctl.h>
#include <sys/time.h>
#define LINUX 1
#endif

#include <vector>
#include <ctime>
#include <chrono>
#include <iostream>

#include "Stack.h"

class KeyboardListener
{
	
private:
	vector<unsigned char> active;  // the vector of active keys to listen for
	Stack<unsigned char> keyStack; // the stack of keys pressed 
	int pauseTime = 10; // in millis
	unsigned long long lastTime = 0;  // the last time a key was pressed
public:
	KeyboardListener();
	KeyboardListener(int pt);
	void listen(); // get the key presses and push them to the stack
	unsigned char getKey();  // get key from the stack
	 void addKey(unsigned char keyValue); // add a key to the listen/active vector
	 void setPauseTime(int pt);


};
#endif