#ifndef HUMANPL
#define HUMANPL

#include "Player.h"

class HumanPlayer : public Player
{
private:

public:
	HumanPlayer();
	void init();
	HumanPlayer(string name);
	void init(string name);
	
	Shot aimShot();

};



#endif
