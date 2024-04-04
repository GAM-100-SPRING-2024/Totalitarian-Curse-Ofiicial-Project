#include "player.h"
#include "level.h"
#include "cprocessing.h"
#include <math.h>
#include <stdlib.h>
#include "constants.h"
#include "coins.h"

// COINS
// 
// Level initialization handled by game.c
// Level shifting handled by level.c
// Creates coin layouts x values (separate functions to spawn coins on platforms and ground)
// Those functions will be used by level files to create coin templates specific to particular leves
// Spawn functions be declared in level.h
// Object will be initialized in game.h

typedef struct {
	float coinX;
	float coinY;
	float radius;
	CP_Color coinColor;
	
} Coin;

// Creates Coin using Tile Parameters
void createCoin(Coin* coin, int tileX, int tileY) {
    
    const float coinRadius = 8.0f;

    // Calculate the actual X and Y position for the coin within the tile
    float coinX = tileX * tileWidth + (rand() % (int)tileWidth);
    float coinY = screenHeight - (tileY + 1) + coinRadius + 10; // Add 10 pixels for offset

    // Update the Coin struct with the calculated values
    coin->coinX = coinX;
    coin->coinY = coinY;
    coin->radius = coinRadius;

    // Set the color of the coin with a yellow gradient
    coin->coinColor = CP_Color_CreateGradient(255, 255, 0, 255, 255, 150, coinRadius);

    // Draw the coin
    initCoinShape(coin);
}

// Initializes coin
void initCoinShape(Coin* coin) {
    CP_Graphics_SetColor(coin->coinColor);
    CP_Graphics_DrawCircle(coin->coinX, coin->coinY, coin->radius);
    CP_Graphics_DrawLine(coin->coinX - coin->radius, coin->coinY, coin->coinX + coin->radius, coin->coinY);
}

// Player-Coin Collision
void checkCoinCollision(Player* player, Coin* coins, int numCoins) {
    for (int i = 0; i < numCoins; ++i) {
        // Calculate distance between player and coin
        float distance = CP_Vector_Distance(player->position, CP_Vector_Set(coins[i].coinX, coins[i].coinY));

        // If the distance is less than the sum of player's size and coin's radius, collision occurs
        if (distance < player->size + coins[i].radius) {
            // Remove the coin from the game world (set its position off-screen)
            coins[i].coinX = -10000;
            coins[i].coinY = -10000;

            // Increase player's score by 5
            player->score += 5;
        }
    }
}

// Function to create coins at specific positions defined in an array
void createCoinsAtPositions(Coin* coins, int numCoins, CP_Vector* positions) {
    for (int i = 0; i < numCoins; ++i) {
        createCoin(&coins[i], positions[i].x, positions[i].y);
    }
}

// COIN TEMPLATES

// LEVEL 0
// 
// Room 2 Coins
void placeCoins001(Coin* coins) {
    // Define positions for coins using vectors
    CP_Vector coinPositions[] = {
        CP_Vector_Set(5.0f, 5.0f),
        CP_Vector_Set(10.0f, 5.0f),
        CP_Vector_Set(15.0f, 5.0f),
        CP_Vector_Set(20.0f, 5.0f),
        CP_Vector_Set(25.0f, 5.0f),
        CP_Vector_Set(7.0f, 10.0f),
        CP_Vector_Set(12.0f, 10.0f),
        CP_Vector_Set(17.0f, 10.0f),
        CP_Vector_Set(22.0f, 10.0f),
        CP_Vector_Set(27.0f, 10.0f)
    };

    // Create coins at specified positions
    createCoinsAtPositions(coins, 10, coinPositions);
}

// Room 3 Coins
void placeCoins002(Coin* coins) {
    // Define positions for coins using vectors
    CP_Vector coinPositions[] = {
        CP_Vector_Set(5.0f, 5.0f),
        CP_Vector_Set(10.0f, 5.0f),
        CP_Vector_Set(15.0f, 5.0f),
        CP_Vector_Set(20.0f, 5.0f),
        CP_Vector_Set(25.0f, 5.0f),
        CP_Vector_Set(7.0f, 10.0f),
        CP_Vector_Set(12.0f, 10.0f),
        CP_Vector_Set(17.0f, 10.0f),
        CP_Vector_Set(22.0f, 10.0f),
        CP_Vector_Set(27.0f, 10.0f)
    };

    // Create coins at specified positions
    createCoinsAtPositions(coins, 10, coinPositions);
}

// Room 4 Coins
void placeCoins003(Coin* coins) {
    // Define positions for coins using vectors
    CP_Vector coinPositions[] = {
        CP_Vector_Set(5.0f, 5.0f),
        CP_Vector_Set(10.0f, 5.0f),
        CP_Vector_Set(15.0f, 5.0f),
        CP_Vector_Set(20.0f, 5.0f),
        CP_Vector_Set(25.0f, 5.0f),
        CP_Vector_Set(7.0f, 10.0f),
        CP_Vector_Set(12.0f, 10.0f),
        CP_Vector_Set(17.0f, 10.0f),
        CP_Vector_Set(22.0f, 10.0f),
        CP_Vector_Set(27.0f, 10.0f)
    };

    // Create coins at specified positions
    createCoinsAtPositions(coins, 10, coinPositions);
}

// Room 5 Coins
void placeCoins004(Coin* coins) {
    // Define positions for coins using vectors
    CP_Vector coinPositions[] = {
        CP_Vector_Set(5.0f, 5.0f),
        CP_Vector_Set(10.0f, 5.0f),
        CP_Vector_Set(15.0f, 5.0f),
        CP_Vector_Set(20.0f, 5.0f),
        CP_Vector_Set(25.0f, 5.0f),
        CP_Vector_Set(7.0f, 10.0f),
        CP_Vector_Set(12.0f, 10.0f),
        CP_Vector_Set(17.0f, 10.0f),
        CP_Vector_Set(22.0f, 10.0f),
        CP_Vector_Set(27.0f, 10.0f)
    };

    // Create coins at specified positions
    createCoinsAtPositions(coins, 10, coinPositions);
}







