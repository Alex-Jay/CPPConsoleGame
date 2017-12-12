#ifndef GAME_UTILITY
#define GAME_UTILITY

#include <string>
#include <windows.h>
#include "Constants.h"

namespace GameUtility
{
	void GotoXY(int, int);
	void GotoXY(int, int, std::string);
	void ClearMenu(int, int);
}
#endif // !GAME_UTILITY
