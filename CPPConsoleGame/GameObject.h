#pragma once
#include <string>
class GameObject
{
private:
	int m_ID;
	std::pair<int, int> m_coordinates;
	bool m_isbreakable;
public:
	GameObject(std::pair<int, int> coordinates);
	GameObject();
	std::pair<int, int> getCoordinates();
	void setCoordinates(int x, int y) { m_coordinates.first = x; m_coordinates.second = y; };
	int getXPos() { return m_coordinates.first; }
	int getYPos() { return m_coordinates.second; }
	bool getBreakable();
	std::string toString();
	~GameObject();
};

