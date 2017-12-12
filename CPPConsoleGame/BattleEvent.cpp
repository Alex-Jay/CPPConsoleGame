#include "stdafx.h"
#include "BattleEvent.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>


BattleEvent::BattleEvent() 
{
}
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto
void BattleEvent::EventLoop(Player player, Monster enemy)
{
	int menu_item = 0, x = 26;
	bool running = true;
	bool eDead = false;
	int count = 0;
	gotoXY(10, 26); cout << "Battle";
	gotoXY(18, 26); cout << "->";

	while (running)
	{
		gotoXY(20, 26);  cout << "1) Attack!";
		gotoXY(20, 27);  cout << "2) Defend!";
		gotoXY(20, 28);  cout << "3) Run!";


		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 28) //down button pressed
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 26) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) 
			{
			case 0:
				gotoXY(0, 30);
				enemy.decreaseHealth(player.Attack(enemy.getDefence()));
				break;

			case 1:
				gotoXY(0, 28);
				player.Defend();
				break;

			case 2:
				gotoXY(0, 32);
				cout << "You Ran!";
				running = false;
				break;
			}

			if (enemy.getHealth() != 0)
			{
				gotoXY(0, 31);
				player.decreaseHealth(enemy.Attack(player.getDefence(), player.isDefend()));
			}
			else {
				running = false;
				gotoXY(0, 26);  std::cout << std::string(60, ' ');
				gotoXY(0, 27);  std::cout << std::string(60, ' ');
				gotoXY(0, 28);  std::cout << std::string(60, ' ');
				gotoXY(0, 29);  std::cout << std::string(60, ' ');
				gotoXY(0, 30);  std::cout << std::string(60, ' ');
				gotoXY(0, 31);  std::cout << std::string(60, ' ');
			}
		}

		gotoXY(20, 23);

	}
}

void BattleEvent::gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

BattleEvent::~BattleEvent()
{
}
