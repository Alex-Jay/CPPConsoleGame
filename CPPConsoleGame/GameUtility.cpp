#include "stdafx.h"
#include "GameUtility.h"
#include <iostream>

namespace GameUtility
{
	HANDLE console;
	COORD CursorPosition;

	void GameUtility::GotoXY(int X, int Y)
	{
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		CursorPosition.X = X;
		CursorPosition.Y = Y;
		SetConsoleCursorPosition(console, CursorPosition);
	}

	void GameUtility::GotoXY(int X, int Y, std::string text)
	{
		GotoXY(X, Y);
		std::cout << text;
	}
}