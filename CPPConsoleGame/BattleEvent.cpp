#include "stdafx.h"
#include "BattleEvent.h"
#include "Constants.h"
#include "GameUtility.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace GameUtility;

BattleEvent::BattleEvent() 
{
}

void BattleEvent::EventLoop(Player &player, Monster &enemy, Engine42* engine)
{
	int tempEnemyXPos = 0, tempEnemyYPos = 0;
	int menu_item = 0, x = 26;
	bool running = true;
	bool eDead = false;
	int count = 0;
	GotoXY(10, 26); cout << "Battle";
	GotoXY(18, 26); cout << "->";

	while (running)
	{
		GotoXY(20, 26);  cout << "1) Attack!";
		GotoXY(20, 27);  cout << "2) Defend!";
		GotoXY(20, 28);  cout << "3) Run!";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 28) //down button pressed
		{
			GotoXY(18, x); cout << "  ";
			x++;
			GotoXY(18, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 26) //up button pressed
		{
			GotoXY(18, x); cout << "  ";
			x--;
			GotoXY(18, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) 
			{
			case ATTACK: // Attack Case
				GotoXY(0, 30);
				tempEnemyXPos = enemy.getXPos(), tempEnemyYPos = enemy.getYPos();

				//if (enemy.getHealth() > 0) // If Enemy is Still Alive
				if(!enemy.checkIsDead())
				{
					enemy.decreaseHealth(player.Attack(enemy.getDefence()));
				}
				else // If Enemy is Dead
				{
					enemy.setIsDead(true);
					(*engine).GetMap().at(player.getYPos()).at(player.getXPos()) = ' ';
					player.setCoordinates(tempEnemyXPos, tempEnemyYPos - 2); // Move The Player Away From The Enemy [ Win Condition ]

					running = false;
				}
				break;

			case DEFEND: // Defend Case
				GotoXY(0, 28);
				player.Defend();
				break;

			case RUN: // Run Case
				tempEnemyXPos = enemy.getXPos(), tempEnemyYPos = enemy.getYPos();

				GotoXY(0, 32);
				cout << "You Ran!";
				
				enemy.setIsDead(false);

				Sleep(DISPLAY_TIME);

				GotoXY(0, 32);
				cout << std::string(8, ' ');

				player.setCoordinates(tempEnemyXPos, tempEnemyYPos - 2); // Move The Player Away From The Enemy [ Run Condition ]

				running = false;
				break;
			}

			if (enemy.getHealth() > 0)
			{
				GotoXY(0, 31);
				player.decreaseHealth(enemy.Attack(player.getDefence(), player.isDefend()));
			}
			else 
			{
				enemy.setIsDead(true);
				running = false;
				GotoXY(0, 26);  std::cout << std::string(60, ' ');
				GotoXY(0, 27);  std::cout << std::string(60, ' ');
				GotoXY(0, 28);  std::cout << std::string(60, ' ');
				GotoXY(0, 29);  std::cout << std::string(60, ' ');
				GotoXY(0, 30);  std::cout << std::string(60, ' ');
				GotoXY(0, 31);  std::cout << std::string(60, ' ');
			}
		}

		GotoXY(20, 23);

	}
}
