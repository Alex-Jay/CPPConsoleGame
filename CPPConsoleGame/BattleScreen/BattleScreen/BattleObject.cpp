#include "stdafx.h"
#include "BattleObject.h"



BattleObject::BattleObject(int health, string name, int attack, int defence) : m_id(1), m_health(health), m_name(name), m_attack(attack), m_defence(defence), m_defend(false)
{
	
	std::cout << "object has been created\n";
}
BattleObject::BattleObject(int health, string name, int attack, int defence, Weapon weapon) : m_id(1), m_health(health), m_name(name), m_attack(attack), m_defence(defence), m_defend(false), m_weapon(weapon)
{
	std::cout << "object has been created\n";
}

string BattleObject::getName()
{
	return m_name;

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
void BattleObject::decreaseHealth(int damage) // set health
{
	cout << m_name << " has taken " << to_string(damage) << ", ";
	m_health -= damage;
	if (m_health < 1)
	{
		m_health = 0;
	}
	cout << m_name << " has " << to_string(m_health) << " remaining!\n";
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
void BattleObject::gainHealth(int heal)
{
	m_health += heal;
}
void BattleObject::Attack(BattleObject& bo)
{
	int currentAttack = m_attack + m_weapon.getAttack(), curentDefence = bo.getDefence() + bo.getWeapon().getDefence() ,damage;
	if (bo.isDefend() == false)
	{
		damage = (2 * currentAttack) - bo.getDefence();
	}
	else
	{
		damage = ((2 * currentAttack) - (bo.getDefence() * 3));
		bo.Defend();
	}
	if (damage < 1)
	{
		damage = 1;
	}
	bo.decreaseHealth(damage);
}
void BattleObject::Defend()
{
	if (m_defend == true)
	{
		m_defend = false;
	}
	else
	{
		m_defend = true;
	}
}
void BattleObject::setWeapon(Weapon n)
{
	m_weapon = n;
}
BattleObject::~BattleObject()
{
}