#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

typedef std::vector<std::string> StringList;

class Menu
{
private:
	int m_Height, m_Width, m_XPos, m_YPos;
	StringList m_MenuComponentList;
public:
	Menu();
	Menu(int, int, int, int);

	int DrawOnce = true;
	int MenuIsOpen = false;

	// Accessors & Mutators
	int GetHeight() { return m_Height; };
	int GetWidth() { return m_Width; };
	int GetXPos() { return m_XPos; };
	int GetYPos() { return m_YPos; };
	StringList& GetMenuComponentList() { return m_MenuComponentList; };
	void SetHeight(int val) { m_Height = val; };
	void SetWidth(int val) { m_Width = val; };
	void SetXPos(int val) { m_XPos = val; };
	void SetYPos(int val) { m_YPos = val; };
	void SetMenuComponentList(StringList& list) { m_MenuComponentList = list; };
	void AddMenuComponent(std::string component) { m_MenuComponentList.push_back(component); }; // Push a component into the list

	void OpenMenu();
	void Draw();
	void GotoXY(int, int);
	void PrintComponents(StringList&);
};

