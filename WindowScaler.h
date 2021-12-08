#ifndef WINSCALETN
#define WINSCALETN

class WindowScaler
{
private:
	int inMin;
	int inMax;
	int outMin;
	int outMax;
public:
	WindowScaler();
	WindowScaler(int i, int j, int k, int l);
	WindowScaler(int k, int l);

	int getVal(int i);
	double getDoubleVal(double x);
};
#endif