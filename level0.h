#pragma once

#include "cprocessing.h"

// Player and Platform forward declarations
typedef struct Player Player;
typedef struct TileInfo TileInfo;

// Define constants
//struct



// Project Functions
void initLevel0(Player* player, Coin* coins);
void generateCoinsForRoom(Coin* coins, int numCoins, int(*positions)[2]);
void drawLevel0(void);
void updateLevel0();
void exitLevel0(void);

