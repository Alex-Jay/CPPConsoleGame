#include "stdafx.h"
#include "Player.h"
#include "GameObject.h"
#include <vector>

Player::Player() {}

Player::Player(std::pair<int, int> coordinates, string name, BattleObject x) : GameObject(coordinates), m_name(""), m_battle(x)
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

void Player::SetCooridnates(int x, int y)
{
	GameObject::setCoordinates(x,y);
}

string Player::toString()
{
	string items;
	for (int i = 0; i < m_inventory.size(); i++) items += getItem(i) + "\n";
	return  m_name + " " + "'inventory:\n " + items  + " Position at: " + GameObject::toString() + m_battle.toString();
}

BattleObject* Player::getBattleOb()
{
	return &m_battle;
}

Player::~Player()
{
}
