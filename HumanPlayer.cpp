#include "HumanPlayer.h"



HumanPlayer::HumanPlayer() : Player()
{
	oldPower = 100;
	oldAngle = 40;
	isCPU = false;
	oldWeapon = new Stash();
}
HumanPlayer::HumanPlayer(string name) : Player(name)
{
	oldPower = 100;
	oldAngle = 40;
	isCPU = false;
	oldWeapon = new Stash();
}
void HumanPlayer::init()
{
	oldPower = 100;
	oldAngle = 40;
	Player::init();
	isCPU = false;
	oldWeapon = new Stash();
}
void HumanPlayer::init(string name)
{
	oldPower = 100;
	oldAngle = 40;
	Player::init(name);
	isCPU = false;
	oldWeapon = new Stash();
}


Shot HumanPlayer::aimShot()
{
// get user input and get shot.
	// also get weapon


	Shot s;
	s.setAngle(oldAngle);
	s.setPower(oldPower / 3.0);
	s.setWeapon(oldWeapon->useUpWeapon());
	s.setStartX(tank.getX() + 2);
	s.setStartY(tank.getY());


	return s;
}
bool HumanPlayer::aimMenu(Console& c, WindowScaler& winX, WindowScaler& winY)
{
	KeyboardListener keys = KeyboardListener(120);
	keys.addKey('W');
	keys.addKey('P');
	keys.addKey('Q');
	keys.addKey('A');
	keys.addKey(VK_ESCAPE);
	keys.addKey(VK_RETURN);
	keys.addKey(VK_UP);
	keys.addKey(VK_DOWN);
	int weaponNumber = 0;
	int power = oldPower;
	int angle = oldAngle;
	bool adjustWeapon = false;
	bool adjustPower = false;
	bool adjustAngle = false;
	vector<Stash*> weaponSelections = getWeapons();
	if (weaponSelections.size() == 0)
	{
		return false;
	}
	while (true)
	{
		if (weaponNumber >= weaponSelections.size())
		{
			weaponNumber = 0;
		}
		if (weaponNumber < 0)
		{
			weaponNumber = 0;
		}
		string out = "Weapon (W): " + weaponSelections[weaponNumber]->getWeaponType().getName() + " " + to_string(weaponSelections[weaponNumber]->getRemaining()) + "ct. Damage: " + to_string(weaponSelections[weaponNumber]->getWeaponType().getDamage()) + "    ";
		c.putString(out, winX.getVal(35), winY.getVal(35));
		string out2 = "Power (P): " + to_string(power) + "   ";
		c.putString(out2, winX.getVal(35), winY.getVal(34));
		string out3 = "Angle (A): " + to_string(angle) + "   ";
		c.putString(out3, winX.getVal(35) + out2.length(), winY.getVal(34));
		c.smartRender();

		keys.listen();
		unsigned char inc = keys.getKey();
		if (inc == 'W')
		{
			if (adjustWeapon)
			{
				weaponNumber++;
			}
			adjustWeapon = true;
			adjustPower = false;
			adjustAngle = false;
		}
		else if (inc == 'P')
		{
			if (adjustPower)
			{
				power++;
			}
			adjustWeapon = false;
			adjustPower = true;
			adjustAngle = false;
		}
		else if (inc == 'A')
		{
			if (adjustAngle)
			{
				angle++;
			}
			adjustWeapon = false;
			adjustPower = false;
			adjustAngle = true;
		}
		else if (inc == VK_UP)
		{
			if (adjustWeapon)
			{
				weaponNumber++;
			}
			if (adjustPower)
			{
				power++;
			}
			if (adjustAngle)
			{
				angle++;
			}
			
		}
		else if (inc == VK_DOWN)
		{
			if (adjustWeapon)
			{
				weaponNumber--;
			}
			if (adjustPower)
			{
				power--;
			}
			if (adjustAngle)
			{
				angle--;
			}
		}
		else if (inc == VK_RETURN)
		{
			break;
		}
		if (power < 0)
		{
			power = 0;
		}
		if (angle < 0)
		{
			angle = 360;
		}
		if (power > 100)
		{
			power = 100;
		}
		if (inc != 0)
		{
			//cout << "ABC!";
			c.smartRender();
		}
		GameContainer::sleep(25);
	}
	oldPower = power;
	oldAngle = angle;
	oldWeapon = weaponSelections[weaponNumber]; // , weaponSelections[weaponNumber].getRemaining());

	return true;
	
	
}
