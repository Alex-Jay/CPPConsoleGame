// CA2RyanAndAlex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameObject.h"
#include "NPC.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main()
{
	std::pair<int, int> coordinate;
	GameObject gO(coordinate);
	string name = "toby", d1 = "My name is toby, the main man", d2 = "My daughter is kidnapped or something, weird lol",
		d3 = "I don't know her name, her mother named her and this is a deeply misogynistic time";
	vector<string> dialogue;
	dialogue.push_back(d1);
	dialogue.push_back(d2);
	dialogue.push_back(d3);
	int health = 10;
	vector<string> inventory;
	string pname = "YoloSwagger", i1 = "Lube", i2 = "More Lube",
		i3 = "FleshLight";
	inventory.push_back(i1);
	inventory.push_back(i2);
	inventory.push_back(i3);
	NPC npc(coordinate, name, dialogue, health);
	Player player(coordinate, pname, inventory, health);
	Monster monster(coordinate, "ghost", inventory, health);
	std::cout << gO.toString() << std::endl;
	std::cout << npc.toString() << std::endl;
	std::cout << player.toString() << std::endl;
	std::cout << monster.toString() << std::endl;

    return 0;
	system("PAUSE");
}

