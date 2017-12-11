#pragma once
#include "GameObject.h"
#include "BattleObject.h"
#include <string>
#include <vector>
using namespace std;
class Monster :
	public GameObject
{
private :
	string m_name;
	vector<string> m_drops;
	BattleObject m_battle;
public:
	Monster(std::pair<int, int> coordinates, string name, vector<string> drops, BattleObject battle);
	string getName();
	BattleObject getBattleOb();
	vector<string> getDrops();
	string toString();
	~Monster();
};

