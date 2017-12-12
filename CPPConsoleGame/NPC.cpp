#include "stdafx.h"
#include "NPC.h"
#include <vector>

NPC::NPC() {};

NPC::NPC(std::pair<int, int> coordinates, string name, vector<string> dialogue, int health) : m_name(name), m_dialogue(dialogue), m_health(health)
{


}

string NPC::getName()
{
	return m_name;
}
vector<string> NPC::getDialogue()
{
	return m_dialogue;
}
string NPC::getDialogueSeg(int num)
{
    return m_dialogue.at(num);
}
int NPC::getHealth()
{
	return m_health;
}
string NPC::toString()
{
	string dialogue;
	for (int i = 0; i < m_dialogue.size(); i++) dialogue += getDialogueSeg(i) + "\n";
	return  m_name + " " + "'dialogue: " + dialogue +  "' health: " + to_string(m_health) + " Position at: " + GameObject::toString();
}
NPC::~NPC()
{
}
