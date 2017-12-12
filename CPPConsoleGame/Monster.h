#pragma once
#include "GameObject.h"
#include "BattleObject.h"
#include "Player.h"
#include <string>
#include <vector>
using namespace std;
class Monster :
	public GameObject,
	public BattleObject
//here is the issue
{
private :
	string m_name;
	vector<string> m_drops;
	
public:
	Monster(std::pair<int, int> coordinates, string name, vector<string> drops, int health, int attack, int defence);
	string getName();
	
	vector<string> getDrops();
	Weapon getWeapon();
	int getHealth();
	int getAttack();
	int getDefence();
	bool isDefend();
	void decreaseHealth(int damage);
	void Attack(Player bo);
	void Defend();
	void setWeapon(Weapon n);
	bool checkIsDead();
	bool getIsDead();
	void setIsDead();
	void setHealth(int health);
	string toString();
	~Monster();
};

