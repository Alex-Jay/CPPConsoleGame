#pragma once
#include <string>
#include <iostream>

using namespace std;

class BattleObject
{
private:
	int m_id, m_health, m_attack, m_defence;
	string m_name;
	bool m_defend;


public:
	BattleObject(int health, string m_name, int m_attack, int m_defence);

	string getName();
	int getHealth();
	int getAttack();
	int getDefence();
	bool isDefend();
	void decreaseHealth(int damage);
	void Attack(BattleObject& bo);
	void Defend();
	bool checkIsDead();
	void gainHealth(int heal);
	~BattleObject();
};

