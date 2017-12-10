#include "stdafx.h"
#include "BattleObject.h"



BattleObject::BattleObject(int health, string name, int attack, int defence): m_id(1), m_health(health), m_name(name), m_attack(attack),  m_defence(defence), m_defend(false)
{
	std::cout << "object has been created\n";
}

string BattleObject::getName()
{
	return m_name;

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
void BattleObject::decreaseHealth(int damage)
{
	cout << m_name << " has taken " << to_string(damage) << ", ";
	m_health -= damage;
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
	int damage;
	if (bo.isDefend() == false)
	{
		damage = (2 *this->getAttack()) - bo.getDefence();
	}
	else
	{
		damage = ((2 * this->getAttack()) - (bo.getDefence() * 3));
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
BattleObject::~BattleObject()
{
}
