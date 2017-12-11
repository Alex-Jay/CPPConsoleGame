#pragma once
#include "GameObject.h"
#include "BattleObject.h"
#include <string>
#include <vector>
using namespace std;
class Player :
	public GameObject
{
private:

	std::string m_name;
	std::vector<std::string> m_inventory;
	BattleObject m_battle;
public:
	Player(std::pair<int, int> coordinates, string name, vector<string> inventory,  BattleObject battle);
	string getName();
	vector<string> getInventory();
	string getItem(int num);
	BattleObject getbattleOb();
	string toString();

	~Player();
};
