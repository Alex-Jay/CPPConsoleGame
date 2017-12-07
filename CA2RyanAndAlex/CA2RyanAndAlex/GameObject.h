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
	virtual std::pair<int, int> getCoordinates();
	virtual bool getBreakable();
	int getXPos();
	int getYPos();
	std::string toString();
	~GameObject();
};

