// BattleScreen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BattleObject.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

//void gameLoop()
//{
//	Weapon sword = Weapon("sword", 3, 1);
//	BattleObject p1 = BattleObject(100, "Phil", 5, 5, sword);
//	BattleObject e1 = BattleObject(20, "Ghost", 7, 8);
//	bool eDead = false;
//	int count = 0;
//	do
//	{
//		if (count % 2 == 0)
//		{
//			p1.Attack(e1);
//			e1.Attack(p1);
//		}
//		else
//		{
//			p1.Defend();
//			e1.Attack(p1);
//		}
//		
//		if ((e1.getHealth() < 1) || (p1.getHealth() < 1)) { eDead = true; }
//		count++;
//	} while (!eDead);
//
//	cout << e1.getWeapon().toString();
//	cout << p1.getWeapon().toString();
//
//}
//
//int main()
//{
//
//	gameLoop();
//    return 0;
//}


// Source : http://www.cplusplus.com/forum/beginner/132595/
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

void gotoXY(int, int); // function defined below if this is new to you.

int main()
{
	int menu_item = 0, run, x = 15;
	bool running = true;
	Weapon sword = Weapon("sword", 3, 1);
	BattleObject p1 = BattleObject(100, "Phil", 5, 5, sword);
	BattleObject e1 = BattleObject(20, "Ghost", 7, 8);
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
				p1.Attack(e1);
				break;
			}


			case 1: {
				gotoXY(10, 21);
				p1.Defend();
				break;
			}

			case 2: {
				gotoXY(10, 21);
				cout << "You Ran!";
				running = false;
				break;
			}


			}

		}
		if (e1.getHealth() != 0)
		{
			gotoXY(10, 22);
			e1.Attack(p1);
			gotoXY(10, 23);
			cout << e1.getAttack();
		}
		else {
			running = false;
		}
	}

	gotoXY(20, 23);
	return 0;
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}