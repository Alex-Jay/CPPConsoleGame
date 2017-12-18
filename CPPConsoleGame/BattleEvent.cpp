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

void BattleEvent::EventLoop(Player &player, Monster &enemy, Engine42 &engine)
{
	int tempEnemyXPos = 0, tempEnemyYPos = 0;
	int menu_item = 0, x = 26;
	bool running = true;
	bool eDead = false;
	int count = 0;
	GotoXY(31, 24); cout << "Battle";
	GotoXY(28, 26); cout << "->";

	while (running)
	{
		GotoXY(23, 5); cout << "Health: " << "    ";
		GotoXY(26, 13); cout << "Health: " << "    ";

		// Display Monster Info
		GotoXY(23, 4); cout << "Name: " << enemy.getName();
		GotoXY(23, 5); cout << "Health: " << enemy.getHealth();
		GotoXY(23, 6); cout << "Strength: " << enemy.getAttack();
		GotoXY(23, 7); cout << "Armor: " << enemy.getDefence();

		// Display Player Info
		GotoXY(26, 12); cout << "Name: " << player.getName();
		GotoXY(26, 13); cout << "Health: " << player.getHealth();
		GotoXY(26, 14); cout << "Strength: " << player.getAttack();
		GotoXY(26, 15); cout << "Armor: " << player.getDefence();

		GotoXY(30, 26);  cout << " Attack!";
		GotoXY(30, 27);  cout << " Defend!";
		GotoXY(30, 28);  cout << " Run!";
		
		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 28) //down button pressed
		{
			GotoXY(28, x); cout << "  ";
			x++;
			GotoXY(28, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 26) //up button pressed
		{
			GotoXY(28, x); cout << "  ";
			x--;
			GotoXY(28, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) 
			{
			case ATTACK: // Attack Case
				GotoXY(0, 30);  std::cout << std::string(100, ' ');

				if(enemy.getHealth() > 0)
				{
					GotoXY(23, 5); cout << "Health: " << enemy.getHealth() << " - " << player.Attack(enemy.getDefence());
					Sleep(1000);
					GotoXY(0, 25); enemy.decreaseHealth(player.Attack(enemy.getDefence())); // Player Attack Monster
					GotoXY(23, 5); cout << "                           ";
					GotoXY(23, 5); cout << "Health: " << enemy.getHealth();

				}
				break;

			case DEFEND: // Defend Case
				GotoXY(0, 30);  std::cout << std::string(100, ' ');
				GotoXY(0, 30);
				player.Defend();
				break;

			case RUN: // Run Case
				tempEnemyXPos = enemy.getXPos(), tempEnemyYPos = enemy.getYPos();

				GotoXY(0, 32);
				cout << "You Ran!";

				Sleep(DISPLAY_TIME);

				GotoXY(0, 32); cout << std::string(100, ' ');

				player.setCoordinates(tempEnemyXPos, tempEnemyYPos - 2); // Move The Player Away From The Enemy [ Run Condition ]

				enemy.setIsDead(false);
				running = false;
				break;
			}

				GotoXY(26, 13); cout << "Health: " << player.getHealth() << " - " << enemy.Attack(player.getDefence(), player.isDefend());
				Sleep(1000);
				GotoXY(0, 26); player.decreaseHealth(enemy.Attack(player.getDefence(), player.isDefend())); // Monster Attack Player
				GotoXY(26, 13); cout << "                 ";
				GotoXY(26, 13);; cout << "Health: " << player.getHealth();

				if (player.getIsDead())
				{
					running = false;
					engine.RunDeathScheme();
				}

				if(enemy.getHealth() < 1)
				{
					enemy.setIsDead(true);
					engine.ClearCharFromMap(enemy.getXPos(), enemy.getYPos(), FLOOR); // Remove Monster Char from Where Player is Standing
					running = false;
				}
		}

		//GotoXY(20, 23);
	}
}
