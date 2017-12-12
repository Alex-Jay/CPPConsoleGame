#include "stdafx.h"
#include "Monster.h"


Monster::Monster(std::pair<int, int> coordinates, string name, vector<string> drops, BattleObject battle) : GameObject(coordinates), m_name(name), m_drops(drops), m_battle(battle)
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

BattleObject Monster::getBattleOb()
{
	return m_battle;
}
string Monster::toString()
{
	string drop;
	for (int i = 0; i < m_drops.size(); i++) drop += m_drops.at(i) + "\n";
	return  m_name + " " + "'dialogue: " + drop + " Position at: " + GameObject::toString() + " Battle Stats: " + m_battle.toString();
}


Monster::~Monster()
{
}
