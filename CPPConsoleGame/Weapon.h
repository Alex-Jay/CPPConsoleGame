#pragma once

#include <string>
#include <iostream>
using namespace std;
class Weapon
{

private:
	string m_name;
	int m_id, m_attack, m_defence, m_x, m_y;

public:
	Weapon();
	Weapon(string m_name, int m_attack, int m_defence);

	int getID();
	string getName();
	int getAttack();
	int getDefence();
	string toString();
	void pickedUp();
	void setCoordinates(int x, int y);
	int getX();
	int getY();

	~Weapon();
};

