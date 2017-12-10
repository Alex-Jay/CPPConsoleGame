// BattleScreen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BattleObject.h"
#include <iostream>

using namespace std;

void gameLoop()
{
	BattleObject p1 = BattleObject(100, "Phil", 5, 5);
	BattleObject e1 = BattleObject(20, "Ghost, or the like", 7, 8);
	bool eDead = false;
	int count = 0;
	do
	{
		if (count % 2 == 0)
		{
			p1.Attack(e1);
			e1.Attack(p1);
		}
		else
		{
			p1.Defend();
			e1.Attack(p1);
		}
		if ((e1.getHealth() < 1) || (p1.getHealth() < 1)) { eDead = true; }
		count++;
	} while (!eDead);
}

int main()
{

	gameLoop();
    return 0;
}

