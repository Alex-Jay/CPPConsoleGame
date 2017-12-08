#ifndef ENGINE_42
#define ENGINE_42
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

typedef std::vector<std::vector<char>> MapArray; // Define 2D Vector Array as 'MapArray' for Ease-of-Use
const enum Direction { LEFT, RIGHT, UP, DOWN };

class Engine42
{
private:
	int m_id;
public:
	static int IDCounter;
	bool MapLoaded;
	bool IsRunning;
	HANDLE console;
	COORD CursorPosition;

	MapArray Map; // Using Outer Vectors index as Y-Position and using Inner Vectors index of as X-Poition, Inner Vector Contents Contain Character at Position.

	std::pair<int, int> PlayerPosition;
	const std::string PlayerIcon = "P";
	const std::string FloorTexture = " ";

	Engine42();
	int GetID() { return m_id; };
	void InitializeMap(const std::string);
	void SetConsoleSize(int, int);
	void Update();
	void Run();
	void DrawMap(const std::string);
	void MovePlayer(enum Direction, int MovementSpeed = 80);
	void DebugPosition();
	void ListenKeyInput();
	void GotoXY(int, int);
	void GotoXY(int, int, std::string);
	void LoadMapFile(const std::string);
};
#endif
