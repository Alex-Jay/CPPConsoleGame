#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
using namespace std;
class Player :
	public GameObject
{
private:
	
	std::string m_name;
	std::vector<std::string> m_inventory;
	int m_health;
public:
	Player(std::pair<int, int> coordinates, string name, vector<string> inventory, int health);
	string getName();
	vector<string> getInventory();
	string getItem(int num);
	int getHealth();
	string toString();

	~Player();
};

