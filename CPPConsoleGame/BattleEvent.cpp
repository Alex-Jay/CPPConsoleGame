#include "stdafx.h"
#include "BattleEvent.h"


BattleEvent::BattleEvent(BattleObject player, BattleObject enemy): m_player(player), m_enemy(enemy)
{
}

void BattleEvent::EventLoop()
{
}

BattleEvent::~BattleEvent()
{
}
