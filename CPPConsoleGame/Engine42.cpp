#include "stdafx.h"
#include "Engine42.h"
#include <fstream>
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include "Menu.h"
#include "Player.h"
#include "NPC.h"
#include "Monster.h"

// TODO:
// FIX BUG
// Player Y Position increments in (Y + 10) and then suddenly increments normally in (Y + 1)
//
// BUG LOCATION:
// MovePlayer()

int Engine42::IDCounter = 0;
const int CONSOLE_SIZE[] = { 500, 625 };
const int PLAYER_START_HEALTH = 100;
const int PLAYER_START_ATTACK = 5;
const int PLAYER_START_DEFENSE = 4;

bool MenuTriggered = true;
bool FirstCycle = true;

// Player Values
Player player;
BattleObject playerStatsObj;
std::string PlayerName = "Player";

// NPC Values
NPC npc;
std::vector<std::string> dialogue;
const int NPC_START_HEALTH = 999;

// Monster Values
std::vector<Monster> monsters;
std::vector<std::string> drops;
BattleObject monsterStatsObj;
const int MOB_START_HEALTH = 70;
const int MOB_START_ATTACK = 2;
const int MOB_START_DEFENSE = 2;

// Door Location
Point2D DoorCoordinates;

// Drops
std::vector<Point2D> DropCoordinates;

// Collectible Location
Point2D CollectibleCoordinates;

// Reference Enums
const enum GameObjects { PLAYER = 'P', VILLAGER = 'V', MOB = 'M', SEWER = 'O', DOOR = '"', COLLECTIBLE = '^', DROP = '*', FLOOR = ' ', WALL = 'X' };

Engine42::Engine42() : m_id(IDCounter++), IsRunning(false), MapLoaded(false)
{
	// Initialize Handle For using GotoXY()
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
	SetConsoleSize(CONSOLE_SIZE[0], CONSOLE_SIZE[1]);

	// Load The Map
	LoadMapFile(FILENAME);

	//Draw Map Layout
	DrawMap();

	// Initialize Dialogue
	dialogue.push_back("Hello " + PlayerName + ", Welcome To Kai, City Of Skies.");
	dialogue.push_back("Go on then, Go Explore!");
}

void Engine42::Update()
{
	// Open Menu On First Boot
	if (FirstCycle)
	{
		OpenMenu();
		FirstCycle = false;
	}

	//Listen To Input
	ListenKeyInput();

	DebugPosition();
}

void Engine42::Run()
{
	// Pre-Initialise Spawn Location if Not Found
	player.setCoordinates(4, 6);

	// Initialize Map
	InitializeMap("Map3.txt");

	if (MapLoaded)
	{
		IsRunning = true;
	}

	while (IsRunning)
	{
		Update();
		Draw();
		Sleep(50); // TODO: Add Time System
	}
}

void Engine42::Draw()
{
	//Draw Player Position
	GotoXY(player.getXPos(), player.getYPos(), "P");
}

void Engine42::DrawMap()
{
	//Draw Initialized Map

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
	// Redraw Initialized Map

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
	int PlayerX = player.getXPos(), PlayerY = player.getYPos(); // Retrieve and Copy Player Position Values.

	switch (DIRECTION)
	{
	case RIGHT:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY).at(PlayerX + 1) != WALL) // If Character 1 Space to the Right of Player is NOT a Wall, Move Right
		{
			PlayerX++;
			player.setCoordinates(PlayerX, PlayerY);
		}
		break;

	case LEFT:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY).at(PlayerX-1) != WALL) // If Character 1 Space to the Left of Player is NOT a Wall, Move Left
		{
			PlayerX--;
			player.setCoordinates(PlayerX, PlayerY);
		}
		break;

	case UP:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY-1).at(PlayerX) != WALL) // If Character 1 Space Upwards from Player is NOT a Wall, Move Up
		{
			PlayerY--;
			player.setCoordinates(PlayerX, PlayerY);
		}
		break;

	case DOWN:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position
		if (Map.at(PlayerY+1).at(PlayerX) != WALL) // If Character 1 Space Downwards from Player is NOT a Wall, Move Down
		{
			PlayerY++;
			player.setCoordinates(PlayerX, PlayerY);
		}
		break;
	}
}

void Engine42::OpenMenu()
{
	// Set Menu While Loop
	MenuTriggered = true;

	GotoXY(27,27); std::cout << "->"; // Draw Intial Arrow

	int Menu_Item = 0, CursorXPos = 27;

	while (MenuTriggered)
	{
		// Controls
		GotoXY(30, 27);  std::cout << " Start Game";
		GotoXY(30, 28);  std::cout << " Controls";
		GotoXY(30, 29);  std::cout << " Exit";

		system("PAUSE>NUL"); // Don't print last character

		if (GetAsyncKeyState(VK_DOWN) && CursorXPos < 29) // Down Button pressed
		{
			GotoXY(27, CursorXPos); std::cout << "  ";
			CursorXPos++;
			GotoXY(27, CursorXPos); std::cout << "->";
			Menu_Item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && CursorXPos > 27) // Up Button pressed
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
					RedrawMap();

					MenuTriggered = false; // Disable Menu & Start/Continue Game
					break;
				case 1:
					ClearScreen(); // Clear Game Screen

					GotoXY(0, 0); // Reset Cursor
					LoadDrawMapFile("ControlsScreen.txt"); // Load & Draw Map But Don't Fill Array

					break;
				case 2:
					MenuTriggered = false;
					IsRunning = false;
					break;
			}
		}
	}
}

void Engine42::ClearScreen()
{
	// Clears Game Portion of the Screen
	for (int i = 0; i < Map.size(); i++)
	{
		GotoXY(0, i); std::cout << std::string(Map.at(i).size(), ' ');
	}
}

void Engine42::DebugPosition()
{
	//GotoXY(0, 25);
	//std::cout << "Health: " << "\tArmor: " << "\tQuest Name: ";

	GotoXY(0, 25); std::cout << "Player X: " <<  player.GetCoordinates().first << "\tPlayer Y: " << player.GetCoordinates().second;

	GotoXY(0, 26); std::cout << "NPC X: " << npc.getXPos() << "\tNPC Y: " << npc.getYPos();
}

void Engine42::ListenKeyInput()
{
	// 0x8000 checks the last bit of GetAsyncKeyState return data -> user is holding input
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
	Point2D drop;

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
				// Foreach character on line
				for (char c : line)
				{
					if (c != FLOOR || c != NULL)
					{
						switch (c)
						{
						case PLAYER:
							playerStatsObj = BattleObject(PLAYER_START_HEALTH, PlayerName, PLAYER_START_ATTACK, PLAYER_START_DEFENSE); // Create BattleObject / Player Stats for battles

							player = Player(std::make_pair(X,Y), PlayerName, playerStatsObj);
							player.setCoordinates(X, Y);

							c = ' '; // Clear Player Char from Map Array When Player Position Set

							break;
						case VILLAGER:
							// Instansiate NPC Object with X & Y Positions
							npc = NPC(std::make_pair(X, Y), "Villager", dialogue, NPC_START_HEALTH);
							break;
						case MOB:
							// Instantiate BattleObject
							monsterStatsObj = BattleObject(MOB_START_HEALTH, "Monster", MOB_START_ATTACK, MOB_START_DEFENSE);

							// Add Two Drops
							drops.push_back("Sword of Doom");
							drops.push_back("Golden Spork");

							// Instansiate Monster Object with X & Y Positions
							monsters.push_back(Monster(std::make_pair(X,Y), "Monster", drops, monsterStatsObj));
							break;
						case DOOR:
							// Save Door Coordinates
							DoorCoordinates.X = X;
							DoorCoordinates.Y + Y;
							break;
						case DROP:
							// Save All Drop Locations
							drop = { X,Y };
							DropCoordinates.push_back(drop);
							break;
						case COLLECTIBLE:
							// Save Collectible Location
							CollectibleCoordinates.X = X;
							CollectibleCoordinates.Y = Y;
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

void Engine42::LoadDrawMapFile(const std::string FILENAME)
{
	// Only Loads and Draws A Map e.g. ControlScreen, BattleScreen
	std::ifstream file(FILENAME);
	std::string line;

	if (file.is_open()) // Test if File Opens Successfully
	{
		while (file.good()) // Loop While File Is In A Good State
		{
			getline(file, line);

			if (!line.empty())
			{
				for (char c : line)
				{
					std::cout << c;
				}
			}
			std::cout << std::endl;
		}

		file.close(); // Close File
	}
}