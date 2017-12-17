#include "stdafx.h"
#include "Potion.h"


Potion::Potion(std::pair<int, int> coordinates): m_health(20), GameObject(coordinates)
{
	
}
void Potion::SetCooridnates(int x, int y)
{
	GameObject::setCoordinates(x, y);
}
int Potion::getHealth()
{
	return m_health;
}
void Potion::pickedUp()
{
	cout << "You have picked up a potion worth 20 health!" << endl;
}
Potion::~Potion()
{
}
