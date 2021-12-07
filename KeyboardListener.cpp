#include "KeyboardListener.h"

KeyboardListener::KeyboardListener()
{
	pauseTime = 10;
}
KeyboardListener::KeyboardListener(int pt)
{
	pauseTime = pt;
}

void KeyboardListener::addKey(unsigned char keyValue)
{
	active.push_back(keyValue);
}


void KeyboardListener::listen()
{
	using namespace std;
	using namespace std::chrono;
#ifndef LINUX

	// windows
	 // unsigned long long lastTime = 0;
	for (unsigned int x = 0; x < active.size(); x++)
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

