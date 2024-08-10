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
#include "KeyboardListener.h"

KeyboardListener::KeyboardListener()
{
	pauseTime = 10;
}
KeyboardListener::KeyboardListener(int pt)
{
	pauseTime = pt;
}
void KeyboardListener::setPauseTime(int pt)
{
	pauseTime = pt;
}
void KeyboardListener::addKey(unsigned char keyValue)
{
	active.push_back(keyValue);
}


void KeyboardListener::listen()  // listen for the keys
{
	using namespace std;
	using namespace std::chrono;
#ifndef LINUX

	// windows
	 // unsigned long long lastTime = 0;
	for (unsigned int x = 0; x < active.size(); x++) // go through each key to listen for. If the key is pressed after the time delay, push it to the stack
	{
		SHORT keyState = GetKeyState(active[x]);
		bool isDown = keyState & 0x8000;
		unsigned long long current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		if (isDown && (lastTime + pauseTime) < current)
		{
			//cout << (lastTime + pauseTime) << " " << current << '\n';
			keyStack.push(active[x]);
			lastTime = current;
		}
	}


#endif // 

}
unsigned char KeyboardListener::getKey()
{
	if (keyStack.getSize() != 0)
	{
		return keyStack.pop();
	}
	return 0;
}