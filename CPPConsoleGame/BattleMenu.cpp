#include "stdafx.h"
#include "BattleMenu.h"


BattleMenu::BattleMenu(BattleObject player, BattleObject enemy): m_player(player), m_enemy(enemy)
{
	cout << "An enemy appears";
}


BattleMenu::~BattleMenu()
{
}
