#pragma once

// Milliseconds in a Second
const int SECOND_IN_MILLISECONDS = 1000;

// Menu Enums
const enum BattleState { ATTACK = 0, DEFEND = 1, RUN = 2};

// Object Types
//const enum Type { MONSTER, NPC, COLLECTIBLE, WEAPON };

// Dialogue Delay
const int DIALOGUE_SPEED_DELAY = (int)(0.05 * SECOND_IN_MILLISECONDS); // Cast Float to Int

// Display Delay
const int MENU_HEIGHT = 8;
const int DISPLAY_TIME = 3 * SECOND_IN_MILLISECONDS;

// Console Varialbes
const int CONSOLE_SIZE[] = { 500, 625 };
const int CONSOLE_WIDTH_IN_CHARS = 100;

// Player Stats
const int PLAYER_START_HEALTH = 100;
const int PLAYER_START_ATTACK = 5;
const int PLAYER_START_DEFENSE = 4;

// NPC Stats
const int NPC_START_HEALTH = 999;

// Monster Stats
const int MOB_START_HEALTH = 70;
const int MOB_START_DEFENSE = 2;
