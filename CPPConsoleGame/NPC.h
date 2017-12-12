#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
using namespace std;
class NPC :
	public GameObject
{
private: 
	std::string m_name;
	std::vector<std::string> m_dialogue;
	int m_health;
public:
	NPC();
	NPC(std::pair<int, int> coordinates, string name, vector<string> dialogue, int health);
	string getName();
	std::pair<int, int> GetCoordinates() { return std::make_pair(GameObject::getXPos(), GameObject::getYPos()); }
	vector<string> getDialogue();
	string getDialogueSeg(int num);
	int getHealth();
	string toString();
	~NPC();
};

