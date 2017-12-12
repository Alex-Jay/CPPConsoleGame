#pragma once
#include "BattleObject.h"
class BattleEvent
{
	BattleObject m_player, m_enemy;
public:
	BattleEvent(BattleObject &player,BattleObject &enemy);
	void EventLoop();
	void gotoXY(int x, int y);
	~BattleEvent();
};

