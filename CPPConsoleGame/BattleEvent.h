#pragma once
#include "BattleObject.h"
#include "Player.h"
#include "Monster.h"
class BattleEvent
{
	BattleObject m_player, m_enemy;
public:
	BattleEvent();
	void EventLoop(Player player, Monster enemy);
	void gotoXY(int x, int y);
	~BattleEvent();
};

