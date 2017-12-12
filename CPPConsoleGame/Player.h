#pragma once
#include "GameObject.h"
#include "BattleObject.h"
#include "Monster.h"
#include "Weapon.h"
#include <string>
#include <vector>
using namespace std;
class Player :
	public GameObject,
	public BattleObject
	//isue
{
private:

	std::string m_name;
	std::vector<std::string> m_inventory;
public:
	Player();
	Player(std::pair<int, int>, string, int health, int attack, int defence);
	void SetCooridnates(int, int);
	std::pair<int, int> GetCoordinates() { return std::make_pair(GameObject::getXPos(), GameObject::getYPos()); }
	string getName();
	vector<string> getInventory();
	string getItem(int num);
	Weapon getWeapon();
	int getHealth();
	int getAttack();
	int getDefence();
	bool isDefend();
	void decreaseHealth(int damage);
	void Attack(Monster bo);
	void Defend();
	void setWeapon(Weapon n);
	bool checkIsDead();
	bool getIsDead();
	void setIsDead();
	void setHealth(int health);
	string toString();

	~Player();
};
