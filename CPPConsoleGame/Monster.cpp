#include "stdafx.h"
#include "Monster.h"


Monster::Monster(std::pair<int, int> coordinates, string name, vector<string> drops, int health, int attack, int defence): GameObject(coordinates), BattleObject(health, attack, defence), m_name(name), m_drops(drops)
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

string Monster::toString()
{
	string drop;
	for (int i = 0; i < m_drops.size(); i++) drop += m_drops.at(i) + "\n";
	return  m_name + " " + "'dialogue: " + drop + " Position at: " + GameObject::toString() + " Battle Stats: " + BattleObject::toString();
}
Weapon Monster::getWeapon()
{
	return BattleObject::getWeapon();
}
int Monster::getHealth()
{
	return BattleObject::getHealth();
}
int Monster::getAttack()
{
	return BattleObject::getAttack();
}
int Monster::getDefence()
{
	return BattleObject::getDefence();
}
bool Monster::isDefend()
{
	return BattleObject::isDefend();
}
void Monster::setHealth(int damage)
{
	BattleObject::setHealth( damage);
}
void Monster::decreaseHealth(int damage) // set health
{
	cout  << " has taken " << to_string(damage) << " damage! ";
	BattleObject::setHealth(damage);
	cout << " has " << to_string(BattleObject::getHealth()) << " HP remaining!\n";
	checkIsDead();
}
bool Monster::checkIsDead()
{
	if (getHealth() < 1) 
	{
		return true;
	}
	return false;
}

void Monster::Attack(Player bo)
{
	int currentAttack = BattleObject::getAttack() + BattleObject::getWeapon().getAttack(), curentDefence = BattleObject::getDefence() + bo.getDefence() ,damage;
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

void Monster::Defend()
{
BattleObject::Defend();
}
void Monster::setWeapon(Weapon n)
{
	BattleObject::setWeapon( n);
}
void Monster::setIsDead()
{
	BattleObject::setIsDead();
}
bool Monster::getIsDead()
{
	BattleObject::getIsDead();
}

Monster::~Monster()
{
}
