#include "stdafx.h"
#include "Engine42.h"
#include <fstream>
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include "Menu.h"

int Engine42::IDCounter = 0;
const int CONSOLESIZE[] = { 500,700 };
bool MenuTriggered = true;
bool FirstCycle = true;
const enum GameObjects { PLAYER = 'P', NPC = 'N', MOB = 'M', SEWER = 'O', DOOR = '"', COLLECTIBLE = '^', DROP = '*', FLOOR = ' ', WALL = 'X' };

Engine42::Engine42() : m_id(IDCounter++), IsRunning(false), MapLoaded(false)
{
	// Initialize Handle
	console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Engine42::SetConsoleSize(int height, int width)
{
	// Source: https://stackoverflow.com/questions/21238806/how-to-set-output-console-width-in-visual-studio
	// Solution Author: https://stackoverflow.com/users/2589776/herohuyongtao

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // Retrieves Consoles Dimensions
	MoveWindow(console, r.left, r.top, width, height, TRUE); // Resizes Console
}

void Engine42::InitializeMap(const std::string FILENAME)
{
	// Set Console Size
	SetConsoleSize(500, 700);

	//Draw Map Layout
	DrawMap(FILENAME);
}

void Engine42::Update()
{
	// Open Menu On First Boot
	if (FirstCycle)
	{
		OpenMenu();
		FirstCycle = false;
	}

	// Remove Entities from Map array for Redraw
	//switch (Map.at(PlayerPosition.first).at(PlayerPosition.second))
	//{
	//	case MOB:
	//		// Map.at(PlayerPosition.first).at(PlayerPosition.second) = ' ';
	//		break;
	//	case DROP:
	//		// Map.at(PlayerPosition.first).at(PlayerPosition.second) = ' ';
	//		break;
	//	case COLLECTIBLE:
	//		// Map.at(PlayerPosition.first).at(PlayerPosition.second) = ' ';
	//		break;
	//}

	//Listen To Input
	ListenKeyInput();

	//DebugPosition();
}

void Engine42::Run()
{
	//Pre-Initialise Spawn Location if Not Found
	PlayerPosition.first = 4; // X Position
	PlayerPosition.second = 6; // Y Position

	InitializeMap("Map3.txt");

	if (MapLoaded)
	{
		IsRunning = true;
	}

	while (IsRunning)
	{
		Update();
		Draw();
		Sleep(50);
	}
}

void Engine42::Draw()
{
	GotoXY(PlayerPosition.first, PlayerPosition.second, "P"); //Stringify Icon
}

void Engine42::DrawMap(const std::string FILENAME)
{
	LoadMapFile(FILENAME);

	m_MapName = FILENAME;

	if (MapLoaded)
	{
		system("CLS");

		for (auto YPos : Map)
		{
			for (auto XPos : YPos)
			{
				std::cout << XPos;
			}
			std::cout << "\n";
		}
	}
	else
	{
		std::cout << "Map Was Not Loaded Successfully." << std::endl;
	}
}

void Engine42::RedrawMap()
{
	GotoXY(0, 0); // Reset cursor before redrawing the map
	for (auto& YPos : Map)
	{
		for (auto& XPos: YPos)
		{
			std::cout << XPos;
		}
		std::cout << std::endl;
	}
}

void Engine42::MovePlayer(enum Direction DIRECTION, int MovementSpeed)
{

	int X = PlayerPosition.first;
	int Y = PlayerPosition.second;
	switch (DIRECTION)
	{
	case RIGHT:
		GotoXY(PlayerPosition.first, PlayerPosition.second, " ");

		if (Map.at(Y).at(X+1) != WALL)
		{
			PlayerPosition.first++;
		}
		break;

	case LEFT:
		GotoXY(PlayerPosition.first, PlayerPosition.second, " ");

		if (Map.at(Y).at(X-1) != WALL)
		{
			PlayerPosition.first--;
		}
		break;

	case UP:
		GotoXY(PlayerPosition.first, PlayerPosition.second, " ");

		if (Map.at(Y-1).at(X) != WALL)
		{
			PlayerPosition.second--;
		}
		break;

	case DOWN:
		GotoXY(PlayerPosition.first, PlayerPosition.second, " ");
		if (Map.at(Y+1).at(X) != WALL)
		{
			PlayerPosition.second++;
		}
		break;
	}
}

void Engine42::OpenMenu()
{
	MenuTriggered = true;

	GotoXY(27,27); std::cout << "->";

	int Menu_Item = 0, CursorXPos = 27;

	while (MenuTriggered)
	{
		GotoXY(30, 27);  std::cout << " Start Game";
		GotoXY(30, 28);  std::cout << " Options";
		GotoXY(30, 29);  std::cout << " Exit";

		system("PAUSE>NUL");

		if (GetAsyncKeyState(VK_DOWN) && CursorXPos < 29) //down button pressed
		{
			GotoXY(27, CursorXPos); std::cout << "  ";
			CursorXPos++;
			GotoXY(27, CursorXPos); std::cout << "->";
			Menu_Item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && CursorXPos > 27) //up button pressed
		{
			GotoXY(27, CursorXPos); std::cout << "  ";
			CursorXPos--;
			GotoXY(27, CursorXPos); std::cout << "->";
			Menu_Item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (Menu_Item)
			{
				case 0:
					// Clear Main Menu
					GotoXY(0, 27);  std::cout << std::string(Map.at(0).size(), ' ');
					GotoXY(0, 28);  std::cout << std::string(Map.at(0).size(), ' ');
					GotoXY(0, 29);  std::cout << std::string(Map.at(0).size(), ' ');
					MenuTriggered = false;
					break;
				case 1:
					break;
				case 2:
					MenuTriggered = false;
					IsRunning = false;
					break;
			}
		}
	}
}

void Engine42::DebugPosition()
{
	GotoXY(0, 25);
	std::cout << "Health: " << "\tArmor: " << "\tQuest Name: ";
}

void Engine42::ListenKeyInput()
{
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
		OpenMenu();
	}
}

void Engine42::GotoXY(int X, int Y)
{
	// Author: whitenite1
	// Source : http://www.cplusplus.com/forum/general/51271/
	CursorPosition.X = X;
	CursorPosition.Y = Y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void Engine42::GotoXY(int X, int Y, std::string text)
{
	CursorPosition.X = X;
	CursorPosition.Y = Y;
	SetConsoleCursorPosition(console, CursorPosition);
	std::cout << text;
}

void Engine42::LoadMapFile(const std::string FILENAME)
{
	int X = 0, Y = 0;
	std::ifstream file(FILENAME);
	std::string line;

	if (file.is_open()) // Test if File Opens Successfully
	{
		Map.clear(); //Clear Map Incase New Map Is Being Loaded

		//Initialise X Position of Map
		std::vector<char> XPos;

		while (file.good()) // Loop While File Is In A Good State
		{
			getline(file, line);

			X = 0; // Reset Value on New Line

			if (!line.empty())
			{
				for (char c : line)
				{
					if (c != FLOOR || c != NULL)
					{
						switch (c)
						{
						case PLAYER:
							PlayerPosition.first = X;
							PlayerPosition.second = Y;
							c = ' ';

							// Instansiate Monster Object with X & Y Positions
							break;
						case NPC:
							// Instansiate NPC Object with X & Y Positions
							break;
						case MOB:
							// Instansiate Monster Object with X & Y Positions
							break;
						case DOOR:
							// Do Door Logic
							break;
						case DROP:
							// Do Drop Object - Randomize Drop?
							break;
						case COLLECTIBLE:
							// Do Collectible Logic
							break;
						}
					}

					X++; // Increment X Position

					// Push Current Character into 'XPos' vector
					XPos.push_back(c);
				}
			}
			// Push Vector of X-Positions and it's corresponding Character
			Map.push_back(XPos);

			XPos.clear(); // Clear X-Position Array for Next Line

			Y++; // Increment Y Position
		}

		file.close(); // Close File

		MapLoaded = true;
	}
}