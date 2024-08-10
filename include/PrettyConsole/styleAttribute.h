#ifndef STYLEATTRIB_H
#define STYLEATTRIB_H 1
#define INVALID_STYLE -1404;


class StyleAttribute
{
private: 
	bool isGood;
	int value;
	int* valueArr;
	bool isArr;
	//int testID;

public:
	StyleAttribute();
	void init(const StyleAttribute& sty,int length);

	void init();
	~StyleAttribute();
	StyleAttribute(int dat);
	void init(int dat);
	StyleAttribute(int* dat,int length);
	void init(int* dat, int length);
	void setArr(int* dat, int length);
	void setValue(int dat);
	bool isSet() const;
	bool isArrOK() const;
	int getValue() const;
	int* getValueArr() const;

	static int testNumber;

};

#endif