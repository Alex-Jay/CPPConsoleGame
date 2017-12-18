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
	if (BattleObject::getHealth() > damage) // If Objects BattleObject instance health is greater than damage, take damage.
	{
		cout << "You have taken " << to_string(damage) << " damage! " << endl;
		BattleObject::setHealth(damage);
	}
	else
	{
		BattleObject::setIsDead(true); // Else set Objects BattleObject instance m_IsDead bool to TRUE.
	}
}
void Player::increaseHealth(int regen) // regenerate health
{
	cout << "You have regained " << to_string(regen) << " health!";
	BattleObject::setHealth(- regen);
}

int Player::Attack(int defence)
{
	int currentAttack = BattleObject::getAttack() + BattleObject::getWeapon().getAttack(), damage;
	if (this->isDefend() == false) {
		damage = (2 * currentAttack) - defence;
	}
	else {
		damage = 2.5*(2 * currentAttack) - defence;
		this->Defend();
	}
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
	cout << m_name << " Has fell in battle!";
	BattleObject::setIsDead(state);
}
bool Player::getIsDead()
{
	return BattleObject::getIsDead();
}

Player::~Player()
{
}
