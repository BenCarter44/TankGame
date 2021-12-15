/*

WindowScaler class


By Benjamin Carter - December 14, 2021


This class uses a mapValue formula which converts a number from the range A-B to C-D (https://www.arduino.cc/reference/en/language/functions/math/map/)

This class allows for things to be scaled on the display. This class puts an imaginary grid on the screen, with the methods getVal and reverse to convert back and forth.


*/

#ifndef WINSCALETN
#define WINSCALETN

class WindowScaler
{
private:
	int inMin; // the bounds of the imaginary scale
	int inMax;
	int outMin; // the bounds of the screen
	int outMax;
public:
	WindowScaler();
	WindowScaler(int i, int j, int k, int l);
	void init();
	void init(int i, int j, int k, int l);      // constructors. (For most classes in this project, the init method and constructor do the same thing. This allows an existing object to be "reset" without risking errors with memory management from copy constructors
	void init(int k, int l);
	WindowScaler(int k, int l);

	int getVal(int i); // get the value
	int getLength(int i);
	double getDoubleVal(double x);
	int getOutMax();
	int getOutMin();
	int getInMax();
	int getInMin();
	int reverse(int absolutePixel); // get the reverse value
};
#endif