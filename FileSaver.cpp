#include "FileSaver.h"
FileSaver::FileSaver()
{

}
FileSaver::FileSaver(string fname)
{
	this->fname = fname;
	

}

void FileSaver::storePlayer(Player* p, Player* p2)
{
	if (getPlayerExists(p->getName()) != -1)
	{
		players[getPlayerExists(p->getName())] = p;
		otherPlayers[getPlayerExists(p->getName())] = p2;
	}
	else
	{
		players.push_back(p);
		otherPlayers.push_back(p2);
	}
	
	// playerName,money,isCPU,tankHP,tankMAX,STASH,playerCPU,CPUMoney,CPU,tankHP,tankMAX,STASH\n

	//STASH: weaponName:damage:amount:weaponName:damage:amount
}
int FileSaver::getPlayerExists(string name)
{
	int out = -1;
	for (int x = 0; x < players.size(); x++)
	{
		if (players[x]->getName() == name)
		{
			out = x;
		}
	}
	return out;
}
Player* FileSaver::getPlayer(string name)
{
	for (int x = 0; x < players.size(); x++)
	{
		if (players[x]->getName() == name)
		{
			return players[x];
		}
	}
	return nullptr;
}
Player* FileSaver::getOtherPlayer(string name)
{
	for (int x = 0; x < players.size(); x++)
	{
		if (players[x]->getName() == name)
		{
			return otherPlayers[x];
		}
	}
	return nullptr;
}
vector<string> FileSaver::getPlayerNames()
{
	vector<string> out;
	for (int x = 0; x < players.size(); x++)
	{
		out.push_back(players[x]->getName());
		
	}
	return out;
}
void FileSaver::saveFile()
{
//	cout << "SAVING!" << endl;
	ofstream  fileIt;
	fileIt.open(fname);
	for (int p = 0; p < players.size(); p++)
	{
		string out = players[p]->getName();
		out += ',';
		out += to_string(players[p]->getMoney());
		out += ',';
		out += to_string(players[p]->isCPUPlayer());
		out += ',';
		out += to_string(players[p]->getTank()->getHP());
		out += ',';
		out += to_string(players[p]->getTank()->getMaxHP());
		out += ',';

		string stash = "";
		vector<Stash*> s = players[p]->getWeapons();
		for (int x = 0; x < s.size(); x++)
		{
			stash += s[x]->getWeaponType().getName();
			stash += ":";
			stash += to_string(s[x]->getWeaponType().getDamage());
			stash += ":";
			stash += to_string(s[x]->getRemaining());
			stash += ":";
		}
		stash = stash.substr(0, stash.length() - 1);
		out += stash;
		out += ',';
		out += otherPlayers[p]->getName();
		out += ',';
		out += to_string(otherPlayers[p]->getMoney());
		out += ',';
		out += to_string(otherPlayers[p]->isCPUPlayer());
		out += ',';
		out += to_string(otherPlayers[p]->getTank()->getHP());
		out += ',';
		out += to_string(otherPlayers[p]->getTank()->getMaxHP());
		out += ',';

		stash = "";
		s.clear();
		s = otherPlayers[p]->getWeapons();
		for (int x = 0; x < s.size(); x++)
		{
			stash += s[x]->getWeaponType().getName();
			stash += ":";
			stash += to_string(s[x]->getWeaponType().getDamage());
			stash += ":";
			stash += to_string(s[x]->getRemaining());
			stash += ":";
		}
		stash = stash.substr(0, stash.length() - 1);
		out += stash;
		out += '\n';
		fileIt << out;
	}
	fileIt.close();

}
void FileSaver::loadFile()
{
//	cout << "loading!\n";
	players.clear();
	otherPlayers.clear();
	badFile = false;
	inout.open(fname, ios::in);
	while (!inout.eof() && !inout.bad() && !inout.fail())
	{
		string dump = "";
		getline(inout, dump, '\n');
		
		string dump2 = "";
		if (inout.eof())
		{
			break;
		}
		//cout << dump << '\n';
		vector<string> tokens;
		dump2 = "";
		for (int x = 0; x < dump.length(); x++)
		{
			if (dump.at(x) == ',')
			{
				
				tokens.push_back(dump2);
				dump2 = "";
			}
			else
			{
				dump2 += dump.at(x);
			}
		}
		 // 5 and 11
		//cout << dump2 << endl;
		tokens.push_back(dump2);
		if (tokens.size() == 12)
		{
			Player* p1;
			Player* p2;
			string stashP1 = tokens[5];
			string stashP2 = tokens[11];
			//cout << stashP1 << endl;
			if (tokens[2] == "0")
			{
				p1 = new HumanPlayer(tokens[0]);
			}
			else
			{
				p1 = new CPUPlayer(tokens[0]);
			}
			if (tokens[8] == "0")
			{
				p2 = new HumanPlayer(tokens[0]);
			}
			else
			{
				p2 = new CPUPlayer(tokens[0]);
			}
			try
			{
				p1->setMoney(stoi(tokens[1]));
				p2->setMoney(stoi(tokens[7]));
				p1->getTank()->setHP(stoi(tokens[3]));
				p2->getTank()->setHP(stoi(tokens[9]));
				p1->getTank()->setMaxHP(stoi(tokens[3]));
				p2->getTank()->setMaxHP(stoi(tokens[9]));
			}
			catch(...)
			{
			//	cout << "Here!";
				badFile = true;
				inout.close();
				return;
			}
			vector<string> subTokens;
			string dump3 = "";
			for (int y = 0; y < stashP1.length(); y++)
			{
				if (stashP1.at(y) == ':')
				{
					subTokens.push_back(dump3);
					dump3 = "";
				}
				else
				{
					dump3 += stashP1.at(y);
				}
			}
			subTokens.push_back(dump3);
			if (subTokens.size() % 3 == 0)
			{
				for (int x = 0; x < subTokens.size() / 3; x++)
				{
					try
					{
						Weapon w = Weapon(subTokens[3 * x], stoi(subTokens[3 * x + 1]));
						Stash st = Stash(w, stoi(subTokens[3 * x + 2]));
						p1->addWeaponStash(st);
					//	cout << w.getName();
					}
					catch (...)
					{
						cout << "Here2!";
						badFile = true;
						inout.close();
						return;
					}
				}
			}
			subTokens.clear();
			dump3 = "";
			for (int y = 0; y < stashP2.length(); y++)
			{
				if (stashP2.at(y) == ':')
				{
					//cout << dump3 << endl;
					subTokens.push_back(dump3);
					dump3 = "";
				}
				else
				{
					dump3 += stashP2.at(y);
				}
			}
			subTokens.push_back(dump3);
			if (subTokens.size() % 3 == 0)
			{
				for (int x = 0; x < subTokens.size() / 3; x++)
				{
					try
					{
						Weapon w = Weapon(subTokens[3 * x], stoi(subTokens[3 * x + 1]));
						Stash st = Stash(w, stoi(subTokens[3 * x + 2]));
						p2->addWeaponStash(st);
					}
					catch (...)
					{

						cout << "Here6!";
						badFile = true;
						inout.close();
						return;
					}
				}
				players.push_back(p1);
				otherPlayers.push_back(p2);
			}
			else
			{
				cout << "Here7!";
				badFile = true;
				return;
			}
		}
		else
		{
			cout << "Here92!";
			badFile = true;
			return;
		}

	}
	
}