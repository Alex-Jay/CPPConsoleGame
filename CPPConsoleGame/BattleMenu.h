#pragma once
#include "BattleObject.h"
#include <iostream>
#include <string>

using namespace std;

class BattleMenu
{
private: 
	BattleObject m_player, m_enemy;
public:
	BattleMenu(BattleObject player, BattleObject enemy);
	~BattleMenu();
};

