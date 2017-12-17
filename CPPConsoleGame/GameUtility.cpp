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

	void GameUtility::ClearMenu(int mapHeight, int clearLength)
	{
		int MENU_YPOS = mapHeight; // Set Top Of Menu Below The Map

		for (int i = 0; i < MENU_HEIGHT; i++)
		{
			GotoXY(0, MENU_YPOS);  std::cout << std::string(clearLength, ' ');
			MENU_YPOS++;
		}
	}

	void GameUtility::DisplayDialogue(std::string text)
	{
		for (int i = 0; i < text.size(); i++)
		{
			std::cout << text.at(i);
			Sleep(DIALOGUE_SPEED_DELAY);
		}
		std::cout << std::endl;
	}
}