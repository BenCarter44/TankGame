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
	vector<unsigned char> active;
	Stack<unsigned char> keyStack;
	int pauseTime = 10; // in millis
	unsigned long long lastTime = 0;
public:
	KeyboardListener();
	KeyboardListener(int pt);
	void listen();
	unsigned char getKey();
	 void addKey(unsigned char keyValue);
	 void setPauseTime(int pt);


};
#endif