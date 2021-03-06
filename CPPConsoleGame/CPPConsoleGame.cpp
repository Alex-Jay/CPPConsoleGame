//
// Title: C++ CA1 Console Game
// Authors: Aleksandrs Jevdokimovs & Ryan Dullaghan
// License: GNU GENERAL PUBLIC LICENSE V3
// Description: C++ Console Game using ASCII characters as visuals.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Engine42.h"

using namespace std;

int main()
{
	Engine42 Engine; // Create Engine Instance

	Engine.Run(&Engine); // Run The Engine & Pass Memory Locaiton of Engine
	
    return 0;
}