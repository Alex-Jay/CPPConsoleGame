#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
using namespace std;
class Monster :
	public GameObject
{
private :
	string m_name;
	int m_health;
	vector<string> m_drops;
public:
	Monster(std::pair<int, int> coordinates, string name, vector<string> drops, int health);
	string getName();
	int getHealth();
	vector<string> getDrops();
	string toString();
	~Monster();
};

