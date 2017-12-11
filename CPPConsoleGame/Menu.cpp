#include "stdafx.h"
#include "Engine42.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include<conio.h>

Menu::Menu()
{
	m_Height = 0;
	m_Width = 0;
	m_XPos = 0;
	m_YPos = 0;
}

Menu::Menu(int height, int width, int x, int y)
{
	m_Height = height;
	m_Width = width;
	m_XPos = x;
	m_YPos = y;
}

void Menu::OpenMenu()
{
	MenuIsOpen = true;
	char KeyPressed;
	while (MenuIsOpen)
	{
		system("pause>nul"); // the >nul bit causes it the print no message
		switch (_getch())
		{
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_RETURN:
			break;
		}
	}
}

void Menu::Draw()
{
	if (DrawOnce)
	{
		GotoXY(GetXPos(), GetYPos()); // Set Cursor Position
		PrintComponents(GetMenuComponentList()); // Iterate and Print from MenuComponentList
		DrawOnce = false; // !DrawOnce Trigger
	}
}

void Menu::PrintComponents(StringList& components)
{
	for (int i = 0; i < components.size(); i++)
	{
		std::cout << components.at(i) << std::endl;
	}
}

void Menu::GotoXY(int X, int Y)
{
	// Author: whitenite1
	// Source : http://www.cplusplus.com/forum/general/51271/
	COORD CursorPosition;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CursorPosition.X = X;
	CursorPosition.Y = Y;
	SetConsoleCursorPosition(console, CursorPosition);
}