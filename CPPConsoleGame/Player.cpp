#include "stdafx.h"
#include "Player.h"
#include <vector>


Player::Player(std::pair<int, int> coordinates, string name, vector<string> inventory, BattleObject battle) : m_name(name), m_inventory(inventory), m_battle(battle)
{


}

string Player::getName()
{
	return m_name;
}
vector<string> Player::getInventory()
{
	return m_inventory;
}
string Player::getItem(int num)
{
	return m_inventory.at(num);
}

string Player::toString()
{
	string items;
	for (int i = 0; i < m_inventory.size(); i++) items += getItem(i) + "\n";
	return  m_name + " " + "'inventory:\n " + items  + " Position at: " + GameObject::toString() + m_battle.toString();
}
BattleObject Player::getbattleOb()
{
	return m_battle;
}

Player::~Player()
{
}
