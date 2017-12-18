#include "stdafx.h"
#include "Engine42.h"
#include "Constants.h"
#include "GameUtility.h"
#include "Math.h"
#include <fstream>
#include <conio.h>
#include <iostream>
#include <string>
#include "Menu.h"
#include "Player.h"
#include "NPC.h"
#include "Monster.h"
#include "BattleEvent.h"
#include "Potion.h"

/*
	TODO: 
	1] Fix Bug with Player Getting Stuck in Fight Loop on Win Condition
	2] Remove the Monster Char from Map Array on Win Condition
	3] 
*/

using namespace GameUtility;

bool IS_GAME_STARTED = false;
bool ENABLE_DEBUGGER = false;

int Engine42::IDCounter = 0;

bool MenuTriggered = true;
bool FirstCycle = true;

// Player Values
Player player;
BattleObject playerStatsObj;
std::string PlayerName = "Player";
bool SpokenToVillager = false;

// NPC Values
NPC npc;
std::vector<std::string> dialogue;
bool notSpoken = true;
int ns = 0;
Weapon villagerDrop = Weapon("Shiny Dagger", 5, 2); // NPC Gives weapon

// Monster Values
std::vector<Monster> monsters;
std::vector<std::string> drops;
BattleObject monsterStatsObj;
int MobStartAttack = 2;

//Weapon Values
Weapon weapons[2]; // Used an array
int weaponNum = 0;

// Door Location
Point2D DoorCoordinates;

// Drops
std::vector<Point2D> DropCoordinates;

// Collectible Location
vector<Potion> potionList;


Engine42::Engine42() : m_id(IDCounter++), IsRunning(false), MapLoaded(false)
{
	// Initialize Handle For using GotoXY()
	//console = GetStdHandle(STD_OUTPUT_HANDLE);
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
	weapons[0] = Weapon("Sword of Doom", 10, 0);
	weapons[1] = Weapon("Golden Spork", 3, 6);

	//Initialize Dialogue
	dialogue.push_back("Hello " + PlayerName + ", Welcome To Kai, City Of Skies.");
	dialogue.push_back("To Move Use Arrow Keys,");
	dialogue.push_back("Collect / Attack / Use by Standing over a Letter.");
	dialogue.push_back("You seem like a decent chap, Here, take this sword.");
	dialogue.push_back("Press ESC > Controls to See Controls Again.");
	dialogue.push_back("Be safe out there, Don't trust anyone.");

	// Set Console Size
	SetConsoleSize(CONSOLE_SIZE[0], CONSOLE_SIZE[1]);

	// Load The Map
	LoadMapFile(FILENAME);
	objectsIntialised = true;
}

// Any Update Logic Here
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

	DetectPlayerCollision(); // Detect Collisions

	// If ENABLE_DEBUGGER is TRUE, Debug()
	if (ENABLE_DEBUGGER)
	{
		Debug();
	}
}

// Game Entry Point
void Engine42::Run(Engine42* engine)
{
	// Initialize Engine Ptr
	m_engine = engine;

	// Pre-Initialise Spawn Location if Not Found
	player.setCoordinates(4, 6);

	// Initialize Starting Map
	InitializeMap("Map3.txt");

	LoadDrawMapFile("Logo.txt");

	if (MapLoaded)
	{
		IsRunning = true;
	}

	while (IsRunning)
	{
		Update(); // Update Logic Every frame	
		Draw(); // Draw Every Frame
		Sleep(50); // FPS. TODO: Add Time System
	}
}

// Any Draw Calls Here
void Engine42::Draw()
{
	//Draw Player Position
	GotoXY(player.getXPos(), player.getYPos(), "P");

	if (!SpokenToVillager)
	{
		GotoXY(55, 16); cout << "< Speak";
	}
}

void Engine42::DrawMap()
{
	//Draw Initialized Map

	if (MapLoaded)
	{
		system("CLS");

		for (auto& YPos : Map)
		{
			for (auto& XPos : YPos)
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
	// Redraw Loaded Map [ Map Location in Engine42.h ]

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
	int PlayerX = player.GetCoordinates().first, PlayerY = player.GetCoordinates().second; // Retrieve and Copy Player Position Values.

	switch (DIRECTION)
	{
	case RIGHT:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY).at(PlayerX + 1) != WALL && Map.at(PlayerY).at(PlayerX+ 1) != VILLAGER) // If Character 1 Space to the Right of Player is NOT a Wall, Move Right
		{
			PlayerX++; // Increment Temporary Player X Position
			player.setCoordinates(PlayerX, PlayerY); // Set Coordinates to new moved location
		}
		break;

	case LEFT:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY).at(PlayerX-1) != WALL && Map.at(PlayerY ).at(PlayerX -1) != VILLAGER) // If Character 1 Space to the Left of Player is NOT a Wall, Move Left
		{
			PlayerX--; // Decrement Temporary Player X Position
			player.setCoordinates(PlayerX, PlayerY); // Set Coordinates to new moved location
		}
		break;

	case UP:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position

		if (Map.at(PlayerY-1).at(PlayerX) != WALL && Map.at(PlayerY -1).at(PlayerX) != VILLAGER) // If Character 1 Space Upwards from Player is NOT a Wall, Move Up
		{
			PlayerY--; // Decrement Temporary Player Y Position
			player.setCoordinates(PlayerX, PlayerY); // Set Coordinates to new moved location
		}
		break;

	case DOWN:
		GotoXY(PlayerX, PlayerY, " "); // Erase Players Current Position
		if (Map.at(PlayerY+1).at(PlayerX) != WALL && Map.at(PlayerY+1).at(PlayerX) != VILLAGER) // If Character 1 Space Downwards from Player is NOT a Wall, Move Down
		{
			PlayerY++; // Increment Temporary Player Y Position
			player.setCoordinates(PlayerX, PlayerY); // Set Coordinates to new moved location
		}
		break;
	}
}

void Engine42::OpenMenu()
{
	//Clear Menu Screen
	ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu -> Map Height, Length to Clear

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
					ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu -> Map Height, Length to Clear

					DrawMap();

					IS_GAME_STARTED = true;
					MenuTriggered = false; // Disable Menu & Start/Continue Game
					break;
				case 1:
					ClearScreen(); // Clear Game Screen

					LoadDrawMapFile("ControlsScreen.txt"); // Load & Draw Map But Don't Fill Array

					break;
				case 2:
					GotoXY(0, 29);  std::cout << std::string(Map.at(0).size(), ' ');
					ENABLE_DEBUGGER = !ENABLE_DEBUGGER; // Trigger Debugger e.g. True = Flase or False = True
					break;
				case 3:
					MenuTriggered = false;
					IsRunning = false;
					break;
			}
		}
	}
}

void Engine42::LoadBattleScreen(Monster &enemy)
{
		BattleEvent current = BattleEvent();

		//Clear Menu
		ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu -> Map Height, Length to Clear

		LoadDrawMapFile("BattleScreen.txt"); // ONLY Draw BattleScreen.txt

		current.EventLoop(player, enemy, *m_engine); // Start Battle Loop

		ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu after Battle -> Map Height, Length to Clear

		RedrawMap(); // Redraw Loaded Map after Battle
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
	GotoXY(0, 25); std::cout << "====== Player Stats ======";
	GotoXY(0, 26); std::cout << " Health: " << player.getHealth();
	GotoXY(0, 27); std::cout << " Defense: " << player.getDefence();
	GotoXY(0, 28); std::cout << " Weapon: " << player.getWeapon().getName();
	GotoXY(0, 29); std::cout << " Attack: " << player.getWeapon().getAttack();
	GotoXY(0, 30); std::cout << " Defense: " << player.getWeapon().getDefence();
	GotoXY(0, 31); std::cout << "==========================";

	//GotoXY(0, 25); std::cout << "Weapon 1 X,Y : " << weapons[0].getX() << ", " << weapons[0].getY();
	//GotoXY(0, 26); std::cout << "Weapon 2 X,Y : " << weapons[1].getX() << ", " << weapons[1].getY();

	//GotoXY(0, 25); std::cout << "Health: " << player.getHealth() << "\tArmor: " << player.getDefence() << "\tWeapon: " << player.getWeapon().getName() << "\tAttack: " << player.getWeapon().getAttack() << "\tDefense: " << player.getWeapon().getDefence();

	//GotoXY(0, 27); std::cout << "Player X: " << player.getXPos() << "\tPlayer Y: " << player.getYPos();
	//GotoXY(0, 26); std::cout << "NPC X: " << player.getBattleOb().toString() << "\tNPC Y: " << npc.getYPos();

	//GotoXY(0, 28); std::cout << "Current Tile: " << Map.at(player.getYPos()).at(player.getXPos());

	//GotoXY(0, 26); std::cout << "NPC X: " << npc.getXPos() << "\tNPC Y: " << npc.getYPos();

	//GotoXY(0, 26); std::cout << "NPC X: " << npc.getXPos() << "\tNPC Y: " << npc.getYPos();

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

void Engine42::RunDeathScheme()
{
	ENABLE_DEBUGGER = false; // Disable Debugger
	IsRunning = false; // Disable Game State

	ClearScreen(); // Clear Draw Screen
	ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Ckear Menu

	GotoXY(20, 10); DisplayDialogue("You Have Died.");
	Sleep(DISPLAY_TIME);

	RestartGame();
}

void Engine42::RestartGame()
{
	weaponNum = 0; // Reset Weapon Count

	MobStartAttack = 2; // Reset Mob Start Attack

	monsters.clear(); // Clear Monsters for New Game

	InitializeMap("Map3.txt"); // Re-Initialize Map

	FirstCycle = true; // Set First Game Cycle to TRUE

	IS_GAME_STARTED = false; // Set bool for Menu

	SpokenToVillager = false; // Restart Start NPC Arrow

	IsRunning = true; // Run Game

	LoadDrawMapFile("Logo.txt");
}

void Engine42::ProcessCharacter(char c, int X, int Y)
{
	Point2D drop;

	if (c != FLOOR || c != NULL) // If Current Character isn't a ' ' or isn't NOT initilized
	{
		switch (c)
		{

		case PLAYER:
			// Instantiate Player Object with BattleObject stats
			player = Player(std::make_pair(X, Y), PlayerName, PLAYER_START_HEALTH, PLAYER_START_ATTACK, PLAYER_START_DEFENSE);
			player.setIsDead(false);
			player.setCoordinates(X, Y);
			break;

		case VILLAGER:
			// Instansiate NPC Object with X & Y Positions
			npc = NPC(std::make_pair(X, Y), "Villager", dialogue, NPC_START_HEALTH);
			break;

		case MOB:
			// Add Two Drops
			drops.push_back("Sword of Doom");
			drops.push_back("Golden Spork");
			MobStartAttack += 1;
			// Instansiate Monster Object with X & Y Positions
			monsters.push_back(Monster(std::make_pair(X, Y), "Monster", drops, MOB_START_HEALTH, MobStartAttack , MOB_START_DEFENSE));
			break;

		case DOOR:
			// Save Door Coordinates
			DoorCoordinates.X = X;
			DoorCoordinates.Y = Y;
			break;

		case WEAPON:
			// Save All Weapon Location
			weapons[weaponNum].setCoordinates(X, Y);
			weaponNum++;
			break;

		case COLLECTIBLE:
			// Save Collectible Location
			potionList.push_back(Potion(std::make_pair(X, Y)));
			break;
		}
	}
}

// = Variable Names Need To Be Cleaned Up for NPC Code =
void Engine42::DetectPlayerCollision()
{
	// Monster Collision Detection
	for (Monster& monster : monsters)
	{
		if (GetDistance(player.GetCoordinates(), std::make_pair(monster.getXPos(), monster.getYPos())) == 0 && !monster.getIsDead()) // If Player is Stood on a Monster
		{
			LoadBattleScreen(monster);
		}
	}

	// Weapon Pickup Collision Detection
	for (Weapon& weapon : weapons)
	{
		if (GetDistance(player.GetCoordinates(), std::make_pair(weapon.getX(), weapon.getY())) == 0) // If Player is Stood on a Weapon
		{
			ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS);

			GotoXY(0, 29); weapon.pickedUp(); // Display Pickup Text
			player.setWeapon(weapon); // Set Players Current Weapon

			ClearCharFromMap(player.getXPos(), player.getYPos(), FLOOR); // Remove Weapon from MapArray

			weapon.setCoordinates(0, 0); // Move Weapon Collision to 0,0 [ Unreachable ]

			Sleep(DISPLAY_TIME); // Display Pickup for DISPLAY_TIME seconds

			ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu -> Map Height, Length to Clear
		}
	}

	// Potion Pickup Collision Detection
	for (Potion& potion : potionList)
	{
		if (GetDistance(player.GetCoordinates(), std::make_pair(potion.getXPos(), potion.getYPos())) == 0) // If Player is Stood on a Weapon
		{
			ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS);

			GotoXY(0, 29); potion.pickedUp(); // Display Pickup Text
			player.increaseHealth(potion.getHealth());

			ClearCharFromMap(potion.getXPos(), potion.getYPos(), FLOOR); // Clear Potion from Map Array on after pickup

			potion.setCoordinates(0, 0);

			Sleep(DISPLAY_TIME); // Display Pickup for DISPLAY_TIME seconds

			ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu -> Map Height, Length to Clear
		}
	}

	// NPC Collision Detection
	//if (GetDistance(player.GetCoordinates(), std::make_pair(npc.getXPos(), npc.getYPos())) > 2)
	//{
	//	notSpoken = true;
	//}
	//else if (GetDistance(player.GetCoordinates(), std::make_pair(npc.getXPos(), npc.getYPos())) == 1
	//			&& notSpoken)
	//{
	//	// Display Dialogue
	//	GotoXY(0,28); DisplayDialogue(npc.getDialogueSeg(ns));

	//	Sleep(DISPLAY_TIME); // Display Dialogue for DISPLAY_TIME seconds
	//	ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu -> Map Height, Length to Clear

	//	ns++;
	//	notSpoken = false;
	//	if (ns >= npc.getDialogue().size())
	//	{
	//		ns = 0;
	//	}
	//}

	if (GetDistance(player.GetCoordinates(), std::make_pair(npc.getXPos(), npc.getYPos())) == 1)
	{
		ENABLE_DEBUGGER = false;

		SpokenToVillager = true;
		GotoXY(55, 16); cout << "         ";

		ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS);

		if (ns < npc.getDialogue().size())
		{
			GotoXY(0, 28); DisplayDialogue(npc.getDialogueSeg(ns));
			Sleep(1000); // Display Dialogue for DISPLAY_TIME seconds
			if (ns == 3)
			{
				ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS);
				player.setWeapon(villagerDrop);
				GotoXY(0, 28); villagerDrop.pickedUp();
				Sleep(2000); // Display Dialogue for DISPLAY_TIME seconds
				ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS);
			}
			if (ns == 5)
			{
				RemoveStartWalls();
			}
			ClearMenu(Map.size(), CONSOLE_WIDTH_IN_CHARS); // Clear Menu -> Map Height, Length to Clear
			ns++;
		}
	}

	// Door Collision Detection
	if (GetDistance(player.GetCoordinates(), std::make_pair(DoorCoordinates.X, DoorCoordinates.Y)) == 0)
	{
		LoadMapFile("Map2.txt"); // Load Map When Walking Through A Door
		RedrawMap(); // Redraw the map
	}
}

int Engine42::GetDistance(pair<int, int> coordOne, pair<int, int> coordTwo) /// takes in two points and returns the difference between them
{

	return sqrt(pow(get<0>(coordOne) - get<0>(coordTwo), 2) + pow(get<1>(coordOne) - get<1>(coordTwo), 2));

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

void Engine42::ClearCharFromMap(int X, int Y, char replaceWith)
{
	MapArray* currentMap = GetMap();
	//this->Map.at(X).at(Y) = replaceWith;
	(*currentMap).at(Y).at(X) = replaceWith;
}

void Engine42::RemoveStartWalls()
{
	for (int i = 1; i < 9; i++)
	{
		ClearCharFromMap(37, i, FLOOR);
		Sleep(200);
		DrawMap();
	}
}