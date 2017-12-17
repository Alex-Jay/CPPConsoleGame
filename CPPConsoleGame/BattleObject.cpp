#include "stdafx.h"
#include "BattleObject.h"


BattleObject::BattleObject()
{

}

BattleObject::BattleObject(int health, int attack, int defence) : m_health(health), m_attack(attack), m_defence(defence), m_defend(false), m_isDead(false)
{
}

BattleObject::BattleObject(int health, int attack, int defence, Weapon weapon) : m_health(health), m_attack(attack), m_defence(defence), m_defend(false), m_weapon(weapon), m_isDead(false)
{

}

Weapon BattleObject::getWeapon()
{
	return m_weapon;
}
int BattleObject::getHealth()
{
	return m_health;
}
int BattleObject::getAttack()
{
	return m_attack;
}
int BattleObject::getDefence()
{
	return m_defence;
}
bool BattleObject::isDefend()
{
	return m_defend;
}

void BattleObject::setHealth(int damage)
{
	m_health -= damage;
	if (m_health < 1)
	{
		m_health = 0;
	}
}
void BattleObject::decreaseHealth(int damage) // set health
{
	cout  << " has taken " << to_string(damage) << " damage! ";
	m_health -= damage;
	if (m_health < 1)
	{
		m_health = 0;
	}
	cout << " has " << to_string(m_health) << " HP remaining!\n";
	checkIsDead();
}
bool BattleObject::checkIsDead()
{
	if (getHealth() < 1) 
	{
		return true;
	}
	return false;
}

void BattleObject::Defend()
{
	if (m_defend == true)
	{
		m_defend = false;
	}
	else
	{
		cout << "Player blocks in prepartion for a critical hit";
		m_defend = true;
	}
}
void BattleObject::setWeapon(Weapon n)
{
	m_weapon = n;
}
void BattleObject::setIsDead(bool state)
{
	m_isDead = state;
}
bool BattleObject::getIsDead()
{
	return m_isDead;
}
string BattleObject::toString()
{
	return  " HP: " + to_string(m_health) + " Atk: " + to_string(m_attack) + " Def: " + to_string(m_defence) + "\n Weapon Stats: " + m_weapon.toString();
}
BattleObject::~BattleObject()
{
}
