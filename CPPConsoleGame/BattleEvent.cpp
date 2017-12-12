#include "stdafx.h"
#include "BattleEvent.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>

BattleEvent::BattleEvent(BattleObject player, BattleObject enemy) : m_player(player), m_enemy(enemy)
{
}
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto
void BattleEvent::EventLoop()
{
	int menu_item = 0, x = 15;
	bool running = true;
	bool eDead = false;
	int count = 0;
	gotoXY(18, 5); cout << "Battle";
	gotoXY(18, 15); cout << "->";

	while (running)
	{
		gotoXY(20, 15);  cout << "1) Attack!";
		gotoXY(20, 16);  cout << "2) Defend!";
		gotoXY(20, 17);  cout << "3) Run!";


		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 17) //down button pressed
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 15) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {

			case 0: {

				gotoXY(10, 21);
				m_player.Attack(m_enemy);
				break;
			}


			case 1: {
				gotoXY(10, 21);
				m_player.Defend();
				break;
			}

			case 2: {
				gotoXY(10, 21);
				cout << "You Ran!";
				running = false;
				break;
			}


			}

			if (m_enemy.getHealth() != 0)
			{
				gotoXY(10, 22);
				m_enemy.Attack(m_player);
				gotoXY(10, 23);
				cout << m_enemy.getAttack();
			}
			else {
				running = false;
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
