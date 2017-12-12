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
	Player();
	Player(std::pair<int, int>, string, BattleObject);
	void SetCooridnates(int, int);
	void MoveLeft();
	std::pair<int, int> GetCoordinates() { return std::make_pair(GameObject::getXPos(), GameObject::getYPos()); }
	string getName();
	vector<string> getInventory();
	string getItem(int num);
	BattleObject* getBattleOb();
	string toString();

	~Player();
};
