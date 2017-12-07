#include "stdafx.h"
#include "Player.h"
#include <vector>


Player::Player(std::pair<int, int> coordinates, string name, vector<string> inventory, int health) : m_name(name), m_inventory(inventory), m_health(health)
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
int Player::getHealth()
{
	return m_health;
}
string Player::toString()
{
	string items;
	for (int i = 0; i < m_inventory.size(); i++) items += getItem(i) + "\n";
	return  m_name + " " + "'inventory:\n " + items + "' health: " + to_string(m_health) + " Position at: " + GameObject::toString();
}

Player::~Player()
{
}
