#include "stdafx.h"
#include "Monster.h"


Monster::Monster(std::pair<int, int> coordinates, string name, vector<string> drops, int health) : m_name(name), m_drops(drops), m_health(health)
{


}

string Monster::getName()
{
	return m_name;
}
vector<string> Monster::getDrops()
{
	return m_drops;
}
int Monster::getHealth()
{
	return m_health;
}
string Monster::toString()
{
	string drop;
	for (int i = 0; i < m_drops.size(); i++) drop += m_drops.at(i) + "\n";
	return  m_name + " " + "'dialogue: " + drop + "' health: " + to_string(m_health) + " Position at: " + GameObject::toString();
}


Monster::~Monster()
{
}
