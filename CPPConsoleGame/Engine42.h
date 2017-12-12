#ifndef ENGINE_42
#define ENGINE_42
#include <iostream>
#include <string>
#include <vector>
#include "BattleObject.h"
#include "Monster.h"

typedef std::vector<std::vector<char>> MapArray; // Define 2D Vector Array as 'MapArray' for Ease-of-Use

// Reference Enums
const enum GameObjects { PLAYER = 'P', VILLAGER = 'V', MOB = 'M', SEWER = 'O', DOOR = '"', COLLECTIBLE = '^', DROP = '*', FLOOR = ' ', WALL = 'X' };
const enum Direction { LEFT, RIGHT, UP, DOWN };

struct Point2D
{
	int X, Y;
};

class Engine42
{
private:
	int m_id;
	std::string m_MapName;
	Engine42* m_engine;
public:
	static int IDCounter;
	bool MapLoaded;
	bool objectsIntialised;
	bool IsRunning;

	MapArray Map; // Using Outer Vectors index as Y-Position and using Inner Vectors index of as X-Poition, Inner Vector Contents Contain Character at Position. Y -> X -> Char

	Engine42();
	int GetID() { return m_id; }
	void InitializeMap(const std::string);
	void SetConsoleSize(int, int);
	MapArray GetMap() { return Map; }
	void Update();
	void Run(Engine42*);
	std::string GetMapName() { return m_MapName; }
	virtual void Draw();
	Engine42* GetEnginePtr() { return m_engine; };
	void DrawMap();
	void RedrawMap();
	void ClearScreen();
	void MovePlayer(enum Direction, int MovementSpeed = 80);
	void Debug();
	void ListenKeyInput();
	void OpenMenu();
	void ProcessCharacter(char, int, int);
	void LoadMapFile(const std::string);
	void LoadDrawMapFile(const std::string);
	void DetectPlayerCollision();
	void LoadBattleScreen(Monster enemy);
};
#endif
