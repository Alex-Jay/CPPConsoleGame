#pragma once
#include "GameObject.h"
#include <iostream>

using namespace std;
class Potion :
	public GameObject
{
private: 
	int m_health;
public:
	Potion(std::pair<int, int> coordinates);
	void SetCooridnates(int, int);
	std::pair<int, int> GetCoordinates() { return std::make_pair(GameObject::getXPos(), GameObject::getYPos()); }
	int getHealth();
	void pickedUp();
	~Potion();
};

