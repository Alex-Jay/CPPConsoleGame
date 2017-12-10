#pragma once
#include "BattleObject.h"
#include <iostream>
#include <string>

using namespace std;

class BattleMenu
{
private: 
	BattleObject m_player;
public:
	BattleMenu(BattleObject player);
	~BattleMenu();
};

