#include "stdafx.h"
#include "GameObject.h"
#include <utility>
#include <string>
#include <iostream> 


GameObject::GameObject(std::pair<int, int> coordinates): m_ID(1), m_coordinates(coordinates), m_isbreakable(false)
{
	

}
GameObject::GameObject()
{
	//std::cout << "This Default Object is created";
}

 std::pair<int, int> GameObject::getCoordinates()
{
	 return m_coordinates;
} 
 bool GameObject::getBreakable()
{
	 return m_isbreakable;
 }

 std::string GameObject::toString()
{
	return "x. " + std::to_string(getXPos()) +  " y. " + std::to_string(getYPos());
}

GameObject::~GameObject()
{
}
