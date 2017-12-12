#pragma once
// Health Bar
const char HEALTH_BAR_CHAR = '=';

// Menu Enums
const enum BattleState { ATTACK = 0, DEFEND = 1, RUN = 2};

// Display Delay
const int SECOND_IN_MILLISECONDS = 1000;
const int MENU_HEIGHT = 8;
const int DISPLAY_TIME = 2 * SECOND_IN_MILLISECONDS;

// Console Varialbes
const int CONSOLE_SIZE[] = { 500, 625 };
const int CONSOLE_WIDTH_IN_CHARS = 50;

// Player Stats
const int PLAYER_START_HEALTH = 100;
const int PLAYER_START_ATTACK = 5;
const int PLAYER_START_DEFENSE = 4;

// NPC Stats
const int NPC_START_HEALTH = 999;

// Monster Stats
const int MOB_START_HEALTH = 70;
const int MOB_START_DEFENSE = 2;
