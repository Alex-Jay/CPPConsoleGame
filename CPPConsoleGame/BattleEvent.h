#pragma once
#include "BattleObject.h"
#include "Player.h"
#include "Monster.h"
#include "Engine42.h"

class BattleEvent
{
public:
	BattleEvent();
	void EventLoop(Player &player, Monster &enemy, Engine42 &engine);
};

