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
#include "BattleEvent.h"

// TODO:
// FIX BUG
// Player Y Position increments in (Y + 10) and then suddenly increments normally in (Y + 1)
//
// BUG LOCATION:
// MovePlayer()

bool IS_GAME_STARTED = false;
bool ENABLE_DEBUGGER = false;
const int MENU_HEIGHT = 10;

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
bool notSpoken = true;
int ns = 0;
const int NPC_START_HEALTH = 999;

// Monster Values
std::vector<Monster> monsters;
std::vector<std::string> drops;
BattleObject monsterStatsObj;
const int MOB_START_HEALTH = 70;
int MobStartAttack = 2;
const int MOB_START_DEFENSE = 2;

//Weapon Values
Weapon weapons[2]; // Used an array
int weaponNum = 0;

// Door Location
Point2D DoorCoordinates;

// Drops
std::vector<Point2D> DropCoordinates;

// Collectible Location
Point2D CollectibleCoordinates;

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

	//Initialize weapons
	Weapon sword = Weapon("Sword of Doom", 10, 0);
	weapons[0] = sword;
	Weapon spork = Weapon("Golden Spork", 3, 6);
	weapons[1] = spork;

	//Initialize Dialogue
	dialogue.push_back("Hello " + PlayerName + ", Welcome To Kai, City Of Skies.");
	dialogue.push_back("Go on then, Go Explore!");

	// Set Console Size
	SetConsoleSize(CONSOLE_SIZE[0], CONSOLE_SIZE[1]);

	// Load The Map
	LoadMapFile(FILENAME);
	objectsIntialised = true;
	//Draw Map Layout
	DrawMap();


}

// Any Update Logic Here
void Engine42::Update()
{
	DetectPlayerCollision();

	// Open Menu On First Boot
	if (FirstCycle)
	{
		OpenMenu();
		FirstCycle = false;
	}

	//Listen To Input
	ListenKeyInput();

	// If Debugger is Active, Debug()
	if (ENABLE_DEBUGGER)
	{
		Debug();
	}
	else
	{
		GotoXY(0, 25); cout << std::string(Map.at(0).size(), ' ');
		GotoXY(0, 26); cout << std::string(Map.at(0).size(), ' ');
	}
}

// Game Entry Point
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
		//if (PlayerCollided())
		//{
		//}

		Update();
		Draw();
		Sleep(50); // TODO: Add Time System
	}
}

// Any Draw Calls Here
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

	for (auto& YPos : Map) // Loop Through all Y Positions
	{
		for (auto& XPos: YPos) // Loop Through all X Positions
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

		if (Map.at(PlayerY).at(PlayerX + 1) != WALL && Map.at(PlayerY).at(PlayerX+ 1) != VILLAGER) // If Character 1 Space to the Right of Player is NOT a Wall, Move Right
		{
			PlayerX++;
			player.setCoordinates(PlayerX, PlayerY);
		}
		break;

	case LEFT:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY).at(PlayerX-1) != WALL && Map.at(PlayerY ).at(PlayerX -1) != VILLAGER) // If Character 1 Space to the Left of Player is NOT a Wall, Move Left
		{
			PlayerX--;
			player.setCoordinates(PlayerX, PlayerY);
		}
		break;

	case UP:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY-1).at(PlayerX) != WALL && Map.at(PlayerY -1).at(PlayerX) != VILLAGER) // If Character 1 Space Upwards from Player is NOT a Wall, Move Up
		{
			PlayerY--;
			player.setCoordinates(PlayerX, PlayerY);
		}
		break;

	case DOWN:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position
		if (Map.at(PlayerY+1).at(PlayerX) != WALL && Map.at(PlayerY+1).at(PlayerX) != VILLAGER) // If Character 1 Space Downwards from Player is NOT a Wall, Move Down
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
		if (!IS_GAME_STARTED)
		{ GotoXY(30, 27);  std::cout << " Start Game"; }
		else { GotoXY(30, 27);  std::cout << " Continue"; }


		GotoXY(30, 28);  std::cout << " Controls";

		if (ENABLE_DEBUGGER){ GotoXY(30, 29);  std::cout << " Debug: ON"; }
		else { GotoXY(30, 29);  std::cout << " Debug: OFF"; }

		GotoXY(30, 30);  std::cout << " Exit";

		system("PAUSE>NUL"); // Don't print last character

		if (GetAsyncKeyState(VK_DOWN) && CursorXPos < 30) // Down Button pressed
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
					//GotoXY(0, 27);  std::cout << std::string(Map.at(0).size(), ' ');
					//GotoXY(0, 28);  std::cout << std::string(Map.at(0).size(), ' ');
					//GotoXY(0, 29);  std::cout << std::string(Map.at(0).size(), ' ');
					//GotoXY(0, 30);  std::cout << std::string(Map.at(0).size(), ' ');

					ClearMenu();

					RedrawMap();

					IS_GAME_STARTED = true;
					MenuTriggered = false; // Disable Menu & Start/Continue Game
					break;
				case 1:
					ClearScreen(); // Clear Game Screen

					LoadDrawMapFile("ControlsScreen.txt"); // Load & Draw Map But Don't Fill Array

					break;
				case 2:
					GotoXY(0, 29);  std::cout << std::string(Map.at(0).size(), ' ');
					ENABLE_DEBUGGER = !ENABLE_DEBUGGER;
					break;
				case 3:
					MenuTriggered = false;
					IsRunning = false;
					break;
			}
		}
	}
}

void Engine42::LoadBattleScreen(Monster enemy)
{
	BattleEvent current = BattleEvent();

	LoadDrawMapFile("BattleScreen.txt"); // ONLY Draw BattleScreen.txt

	current.EventLoop(player, enemy); // Start Battle Loop

	ClearMenu(); // Clear Menu After Battle

	RedrawMap(); // Redraw Loaded Map
}

void Engine42::ClearScreen()
{
	// Clears Game Portion of the Screen
	for (int i = 0; i < Map.size(); i++)
	{
		GotoXY(0, i); std::cout << std::string(Map.at(i).size(), ' ');
	}
}

void Engine42::Debug()
{
	//GotoXY(0, 25);
	//std::cout << "Health: " << "\tArmor: " << "\tQuest Name: ";

	GotoXY(0, 25); std::cout << "Player X: " << player.getXPos() << "\tPlayer Y: " << player.getYPos();
	//GotoXY(0, 26); std::cout << "NPC X: " << player.getBattleOb().toString() << "\tNPC Y: " << npc.getYPos();

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

void Engine42::ProcessCharacter(char c, int X, int Y)
{
	Point2D drop;

	if (c != FLOOR || c != NULL) // If Current Character isn't a ' ' or isn't NOT initilized
	{
		switch (c)
		{

		case PLAYER:
			//playerStatsObj = BattleObject(PLAYER_START_HEALTH, PlayerName, PLAYER_START_ATTACK, PLAYER_START_DEFENSE); // Create BattleObject / Player Stats for battles

			player = Player(std::make_pair(X, Y), PlayerName, PLAYER_START_HEALTH, PLAYER_START_ATTACK, PLAYER_START_DEFENSE);
			player.setCoordinates(X, Y);
			break;

		case VILLAGER:
			// Instansiate NPC Object with X & Y Positions
			npc = NPC(std::make_pair(X, Y), "Villager", dialogue, NPC_START_HEALTH);
			break;

		case MOB:
			// Instantiate BattleObject

			// Add Two Drops
			drops.push_back("Sword of Doom");
			drops.push_back("Golden Spork");
			MobStartAttack += 7;
			// Instansiate Monster Object with X & Y Positions
			monsters.push_back(Monster(std::make_pair(X, Y), "Monster", drops, MOB_START_HEALTH, MobStartAttack , MOB_START_DEFENSE));
			break;

		case DOOR:
			// Save Door Coordinates
			DoorCoordinates.X = X;
			DoorCoordinates.Y = Y;
			break;

		case DROP:
			// Save All Drop Locations
			weapons[weaponNum].setCoordinates(X, Y);
			weaponNum++;
			break;

		case COLLECTIBLE:
			// Save Collectible Location
			CollectibleCoordinates.X = X;
			CollectibleCoordinates.Y = Y;
			break;
		}
	}
}

bool Engine42::PlayerCollided()
{
	for (auto& monsterCoord : monsters)
	{
		if (player.GetCoordinates() == std::make_pair(monsterCoord.getXPos(), monsterCoord.getYPos()) && !monsterCoord.getIsDead())
		{
			LoadBattleScreen(monsterCoord);
			monsterCoord.setIsDead();
			return true;
		}
	}
	if (player.GetCoordinates() == std::make_pair(DoorCoordinates.X, DoorCoordinates.Y))
	{
		//IsRunning = false;
		LoadMapFile("Map2.txt");
		return true;
	}
	for (int i = 0; i < sizeof(weapons); i++)
	{
		if (player.GetCoordinates() == std::make_pair(weapons[i].getX(), weapons[i].getY()))
		{
			GotoXY(0, 30); weapons[i].pickedUp();
			player.setWeapon(weapons[i]);
			weapons[i].setCoordinates(0,0);
			return true;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (player.GetCoordinates() == std::make_pair(npc.getXPos() + 2, npc.getYPos() + 2) || player.GetCoordinates() == std::make_pair(npc.getXPos() - 2, npc.getYPos() - 2))
			{
				notSpoken = true;
			}
			else if ((player.GetCoordinates() == std::make_pair(npc.getXPos() + i, npc.getYPos() + j) || player.GetCoordinates() == std::make_pair(npc.getXPos() - i, npc.getYPos() - j)) && notSpoken)
			{
				GotoXY(0, 28, npc.getDialogueSeg(ns));

				ns++;
				notSpoken = false;
				if (ns > npc.getDialogue().size())
				{
					ns = 0;
				}
				
			}
			
		}
	}
	return false;
}

void Engine42::DetectPlayerCollision()
{
	for (Monster& monster : monsters)
	{
		if (player.GetCoordinates() == std::make_pair(monster.getXPos(), monster.getYPos()) && !monster.getIsDead())
		{
			LoadBattleScreen(monster);
		}
	}

	for (int i = 0; i < sizeof(weapons); i++)
	{
		if (player.GetCoordinates() == std::make_pair(weapons[i].getX(), weapons[i].getY()))
		{
			GotoXY(0, 30); weapons[i].pickedUp();
			player.setWeapon(weapons[i]);
			weapons[i].setCoordinates(0, 0);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (player.GetCoordinates() == std::make_pair(npc.getXPos() + 2, npc.getYPos() + 2))
			{
				notSpoken = true;
			}
			else if (player.GetCoordinates() == std::make_pair(npc.getXPos() + i, npc.getYPos() + j) && notSpoken)
			{
				GotoXY(0,26);
				cout << npc.getDialogueSeg(ns)<< endl;
				ns++;
				notSpoken = false;
				if (ns > npc.getDialogue().size())
				{
					ns = 0;
				}
			}
		}
	}
	if (player.GetCoordinates() == std::make_pair(DoorCoordinates.X, DoorCoordinates.Y))
	{
		LoadMapFile("Map2.txt");
		RedrawMap();
	}


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
				// Foreach character on line
				for (char c : line)
				{
						ProcessCharacter(c, X, Y);
					
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
	
	Map.at(player.getYPos()).at(player.getXPos()) = ' '; // Remove Player character from Map
}

void Engine42::LoadDrawMapFile(const std::string FILENAME)
{
	GotoXY(0, 0); // Reset Cursor

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

void Engine42::ClearMenu()
{
	int MENU_YPOS = 27;

	for (int i = 0; i < MENU_HEIGHT; i++)
	{
		GotoXY(0, MENU_YPOS);  std::cout << std::string(Map.at(0).size(), ' ');
		MENU_YPOS++;
	}
}