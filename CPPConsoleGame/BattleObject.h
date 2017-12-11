#pragma once
#include "Weapon.h"
#include <string>
#include <iostream>

using namespace std;

class BattleObject
{
private:
	int m_health, m_attack, m_defence;
	string m_name;
	bool m_defend;
	Weapon m_weapon;


public:
	BattleObject(int health, string name, int attack, int defence, Weapon weapon);
	BattleObject(int health, string name, int attack, int defence);

	string getName();
	Weapon getWeapon();
	int getHealth();
	int getAttack();
	int getDefence();
	bool isDefend();
	void decreaseHealth(int damage);
	void Attack(BattleObject& bo);
	void Defend();
	void setWeapon(Weapon n);
	bool checkIsDead();
	void gainHealth(int heal);
	string toString();
	~BattleObject();
};

