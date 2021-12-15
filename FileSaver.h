/*

FileSaver class


By Benjamin Carter - December 14, 2021

This class saves a list of players to a file. 

The format for the file is like this:


// playerName,money,isCPU,tankHP,tankMAX,diff,STASH,playerCPU,CPUMoney,CPU,tankHP,tankMAX,diff,STASH\n

	//STASH: weaponName:damage:amount:weaponName:damage:amount

The class can load and save the vector of players. 
The method storePlayer adds a player to the file

saveFile() is required to save the contents to the disk.



*/
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
	string fname;   // the file name
	fstream inout;   // the file handler
	vector<Player*> players;        // player1's
	vector<Player*> otherPlayers;   // player2's
	bool badFile = false;
public:
	FileSaver();
	FileSaver(string fname);

	void storePlayer(Player* p, Player* p2);   // this can store any player object (meaning both Human and CPU players)
	Player* getPlayer(string name);              // get player by name (player1 index)
	Player* getOtherPlayer(string name);  // get player2 by name (player1 index)
	vector<string> getPlayerNames();
	void loadFile();
	void saveFile();   // load and save
	int getPlayerExists(string name);  // utility, but also pubic
	bool isBad()
	{
		return badFile;
	}

};



#endif