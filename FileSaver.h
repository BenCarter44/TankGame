#ifndef FSAVE
#define FSAVE

#include <string>
#include "Player.h"
#include "HumanPlayer.h"
#include "CPUPlayer.h"
#include "Stash.h"
#include <vector>
#include <fstream>
using namespace std;

class FileSaver
{
private:
	string fname;
	fstream inout;
	vector<Player*> players;
	vector<Player*> otherPlayers;
	bool badFile = false;
public:
	FileSaver();
	FileSaver(string fname);

	void storePlayer(Player* p, Player* p2);
	Player* getPlayer(string name);
	Player* getOtherPlayer(string name);
	vector<string> getPlayerNames();
	void loadFile();
	void saveFile();
	int getPlayerExists(string name);
	bool isBad()
	{
		return badFile;
	}

};



#endif