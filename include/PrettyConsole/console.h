#ifndef CONSOLE_H
#define CONSOLE_H


#if defined(_WIN32) || defined(WIN32)
#include <windows.h>

#else
#include <sys/ioctl.h>
#define LINUX 1
#endif
#include "PrettyConsole/row.h"
#include "PrettyConsole/screenComponent.h"


using namespace std;

class Console
{
private:
	Row* rows;
	bool resize;
	int height;
	int width;
	bool support;

public:
	void render();
	Console();
	Console(string t);
	void init();
	void init(string t);
	void fillScreen();
	void clear();
	void putString(string data, int x, int y);
	void putString(string data, int x, int y, Style s);
	void screenTest();
	string stringRender();
	int getWidth() const;
	int getHeight() const;
	void smartRender();
	void addShape(ScreenComponent* sc);
	static int mapValue(int x, int in_min, int in_max, int out_min, int out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
	bool getSupport()
	{
		return support;
	}
	void setTitle(string title);
	Style getSpecificStyle(int x, int y);
	unsigned char getSpecificChar(int x, int y);
};



#endif