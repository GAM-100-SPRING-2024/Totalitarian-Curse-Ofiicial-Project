#include "cprocessing.h"
#include "environment.h"
#include "level.h"
#include "player.h"
#include "coins.h"

// LEVEL
// Creates Levels and Room Array
// Handles Level Shifts and Room Shifts
// Block layouts and block spawing handled by environment.c
// Specific level layouts will be handled by level(n) files

// Structs

int currentRoom = 0;
int currentLevel = 0;

typedef struct{
    int level;
    int numRooms;
} Levels;

Levels levels[5] = {
    {0, 5},
    {1, 10},
    {2, 15},
    {3, 20},
    {4, 1}
};

void init_levels(Player* player, int level, Coin* coins) {
    // Initialize levels with their respective properties
    initLevel0(player, level, coins);
    // Add initialization for other levels as needed
}

void drawLevel(int level, Player* player) {
    // Draw the specified level based on its properties
    for (int i = 0; i < levels[level].numRooms; ++i) {
        if (i == currentRoom) {
            // Draw the current room
            switch (level) {
            case 0:
                drawLevel0(player, i);
                break;
                // Add cases for other levels as needed
            default:
                
                break;
            }
        }
    }
}

void updateLevel(int level, Player* player) {
    // Check for room transitions
    if (player->position.x - player->width / 2 < 0) {
        // Player reached the left edge of the screen
        if (currentRoom > 0) {
            currentRoom--;
        }
    }
    else if (player->position.x + player->width / 2 > CP_System_GetDisplayWidth()) {
        // Player reached the right edge of the screen
        if (currentRoom < levels[level].numRooms - 1) {
            currentRoom++;
        }
    }
    if (currentRoom == levels[level].numRooms - 1) {
        // Prevent the player from going further without fulfilling the win condition
        if (player->score < 100 && level == 0) {
            player->position.x = CP_System_GetDisplayWidth() - player->width / 2;
        }
    }
}

void changeLevel(int level, Player* player) {
    // Update the specified level based on its properties
    switch (level) {
    case 0:
        updateLevel0(player);
        break;
        // Add cases for other levels as needed
    default:
        initLevel0(player, level, coins);
        break;
    }
}
