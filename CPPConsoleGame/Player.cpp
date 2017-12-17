#include "stdafx.h"
#include "Player.h"
#include "GameObject.h"
#include <vector>

Player::Player() {}

Player::Player(std::pair<int, int> coordinates, string name, int health, int attack, int defence) : GameObject(coordinates), BattleObject(health, attack, defence), m_name("")
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
	return  m_name + " " + "'inventory:\n " + items  + " Position at: " + GameObject::toString() + BattleObject::toString();
}
Weapon Player::getWeapon()
{
	return BattleObject::getWeapon();
}
int Player::getHealth()
{
	return BattleObject::getHealth();
}
int Player::getAttack()
{
	return BattleObject::getAttack();
}
int Player::getDefence()
{
	return BattleObject::getDefence();
}
bool Player::isDefend()
{
	return BattleObject::isDefend();
}
void Player::setHealth(int damage)
{
	BattleObject::setHealth(damage);
}
void Player::decreaseHealth(int damage) // set health
{
	cout << " has taken " << to_string(damage) << " damage! ";
	BattleObject::setHealth(damage);
	cout << " has " << to_string(BattleObject::getHealth()) << " HP remaining!\n";
	checkIsDead();
}
void Player::increaseHealth(int regen) // regenerate health
{
	cout << "Has regained " << to_string(regen) << " health!";
	BattleObject::setHealth(- regen);
}
bool Player::checkIsDead()
{
	if (getHealth() < 1)
	{
		return true;
	}
	return false;
}

int Player::Attack(int defence)
{
	int currentAttack = BattleObject::getAttack() + BattleObject::getWeapon().getAttack(), damage;
	
		damage = (2 * currentAttack) - defence;
	
	if (damage < 1)
	{
		damage = 1;
	}
	return damage;
}

void Player::Defend()
{
	BattleObject::Defend();
}
void Player::setWeapon(Weapon n)
{
	BattleObject::setWeapon(n);
}
void Player::setIsDead(bool state)
{
	BattleObject::setIsDead(state);
}
bool Player::getIsDead()
{
	return BattleObject::getIsDead();
}

Player::~Player()
{
}
