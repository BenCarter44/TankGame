#ifndef STYLES_H
#define STYLES_H 1

#include <string>
#include "PrettyConsole/styleAttribute.h"
#include <vector>

using namespace std;

class Style
{
private:
	StyleAttribute textColor;
	StyleAttribute textWeight;
	StyleAttribute backgroundColor;
	StyleAttribute isBlink;
	StyleAttribute border;
	bool reset = true;
	StyleAttribute defaultColors[16];
	
public:
	Style();
	void init();
	Style(const Style& cp);
	void init(const Style& cp);

	~Style()
	{
		
	}
	string getASCII() const;
	void setTextColor(int r, int g, int b);
	void setTextColor(int set);
	void setBackgroundColor(int r, int g, int b);
	void setBackgroundColor(int set);
	void turnOnBlink();
	void turnOffBlink();
	void turnOnFastBlink();
	void setBorderBox();
	void noBorder();
	void setBorderCircle();
	bool isEqual(const Style& cp);
	void mergeStyles(const Style& cp);
	

};








#endif