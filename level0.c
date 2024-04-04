// LEVEL 0 (TUTORIAL LEVEL)
// Biome is Plains Biome
// Level initialization handled by game.c
// Level shifting handled by level.c
// Creates Plains1 and Plains2 Layouts
// Will create Level 0 Coin and Enemy Layouts *future

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "cprocessing.h"
#include "constants.h"
#include "player.h"
#include "platform.h"
#include "coins.h"

// Level 0 (Tutorial Level) Functions

void initLevel0(Player* player, int level, Coin* coins) {
    // Initialize player's properties for Level 0
    player->position = CP_Vector_Set(100, 100); // Set initial position
    player->health = 100; // Set initial health
    player->lives = 5; // Set initial lives
    player->score = 0; // Reset score
    player->currentPlayerLevel = 0;
    player->currentPlayerRoom = 0;

    // Initialize coin layout for Level 0
    int numCoins = 10; // Change this value as needed
    int coinPositions[10][2] = {
        {200, 200}, {300, 300}, // Set coin positions here
        // Add more coin positions as needed
    };
    generateCoinsForRoom(coins, numCoins, coinPositions);
}

void generateCoinsForRoom(Coin* coins, int numCoins, int(*positions)[2]) {
    for (int i = 0; i < numCoins; ++i) {
        createCoin(&coins[i], positions[i][0], positions[i][1]);
    }
}

void drawLevel0(Player* player, int currentRoom) {
    // Draw the tiles, platforms, and coins for the current room
    switch (currentRoom) {
    case 0:
        generatePlains1();
        placePlatform001();
        break;
    case 1:
        placeCoins001();
        placePlatform002();
        break;
    case 2:
        generatePlains2();
        placeCoins002();
        placePlatform003();
        break;
    case 3:
        generatePlains3();
        placeCoins003();
        placePlatform004();
        break;
    case 4:
        generatePlains4();
        placeCoins004();
        break;
    default:
        break;
    }

    // Draw the player
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255)); // Set the fill color to red
    CP_Graphics_DrawRect(player->position.x, player->position.y, player->width, player->height);

    //CP_Image_Draw(player->sprite, player->position.x, player->position.y, player->width, player->height, 255);
}

void updateLevel0(Player* player, int currentRoom) {
    // Update player and environment for the current room
    player_update(player);
    // Add any other update logic for the current room here
    if (currentRoom == levels[currentLevel].numRooms - 1 && player->score >= 100) {
        // Display the win screen
        // (Implement the win screen logic here)
        // For now, we'll just print a message
        printf("You've completed Level 0! Score: %d\n", player->score);
    }
    // Check if the player has reached the right edge of the current room
    else if (player->position.x + player->width / 2 > CP_System_GetWindowWidth()) {
        // Move the player to the left edge of the next room if available
        if (currentRoom < levels[currentLevel].numRooms - 1) {
            currentRoom++;
            player->position.x = 0 + player->width / 2;
        }
    }
    // Check if the player has reached the left edge of the current room
    else if (player->position.x - player->width / 2 < 0) {
        // Move the player to the right edge of the previous room if available
        if (currentRoom > 0) {
            currentRoom--;
            player->position.x = CP_System_GetWindowWidth() - player->width / 2;
        }
    }
}

void exitLevel0() {
    // Clean up resources used by Level 0
    // Free memory allocated for coins, platforms, etc.
}






