//
// Title: C++ CA1 Console Game
// Authors: Aleksandrs Jevdokimovs & Ryan Dullaghan
// License: GNU GENERAL PUBLIC LICENSE V3
// Description: C++ Console Game using ASCII characters as visuals.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <thread>

using namespace std;

const enum Direction { LEFT, RIGHT, UP, DOWN };
std::pair<int, int> PlayerPosition;
const string Map = "XXXXXXXXXXXXXXXXXXXX\nX                  X\nX                  X\nX                  X\nX                  X\nX                  X\nX                  X\nX                  X\nX                  X\nXXXXXXXXXXXXXXXXXXXX";
const string PlayerIcon = "P";
const string FloorTexture = " ";

// Author: whitenite1
// Source : http://www.cplusplus.com/forum/general/51271/
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void GotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void GotoXY(int x, int y, string text)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << text;
}

void InitializeMap()
{
	PlayerPosition.first = 7;
	PlayerPosition.second = 2;
	cout << Map;
}

void MovePlayer(enum Direction DIRECTION, int MovementSpeed = 80)
{
	switch (DIRECTION)
	{
	case RIGHT:
		GotoXY(PlayerPosition.first++, PlayerPosition.second, PlayerIcon);
		GotoXY(PlayerPosition.first - 2, PlayerPosition.second, FloorTexture);
		Sleep(MovementSpeed);
		break;

	case LEFT:
		GotoXY(PlayerPosition.first--, PlayerPosition.second, PlayerIcon);
		GotoXY(PlayerPosition.first + 2, PlayerPosition.second, FloorTexture);
		Sleep(MovementSpeed);
		break;

	case UP:
		GotoXY(PlayerPosition.first, PlayerPosition.second--, PlayerIcon);
		GotoXY(PlayerPosition.first, PlayerPosition.second + 2, FloorTexture);
		Sleep(MovementSpeed);
		break;

	case DOWN:
		GotoXY(PlayerPosition.first, PlayerPosition.second++, PlayerIcon);
		GotoXY(PlayerPosition.first, PlayerPosition.second - 2, FloorTexture);
		Sleep(MovementSpeed);
		break;
	}
}

void DebugPosition()
{
	GotoXY(40, 0);
	cout << "X: " << PlayerPosition.first << "\tY: " << PlayerPosition.second;
	Sleep(20);
}

int main()
{
	bool IsRunning = true;


	InitializeMap();

	while (IsRunning)
	{
		DebugPosition();

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			MovePlayer(UP);
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			MovePlayer(DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			MovePlayer(LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			MovePlayer(RIGHT);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			IsRunning = false;
		}
	}

    return 0;
}