#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon() : m_id(0), m_name("Nothing"), m_attack(0), m_defence(0)
{
	cout << "Nothing equiped!!" << endl;
}
Weapon::Weapon(string name, int attack, int defence) : m_id(1), m_name(name), m_attack(attack), m_defence(defence)
{
	cout << m_name << " equiped!!" << endl;
}

int Weapon::getAttack()
{
	return m_attack;
}

int Weapon::getDefence()
{
	return m_defence;
}

int Weapon::getID()
{
	return m_id;
}

string Weapon::getName()
{
	return m_name;
} 

string Weapon::toString()
{
	return m_name + ", " + to_string(m_id) + " no. " + to_string(m_attack) + " atk, " + to_string(m_defence) + " def\n";
}
Weapon::~Weapon()
{
}
