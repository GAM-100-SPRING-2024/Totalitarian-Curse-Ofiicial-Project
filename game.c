// GAME
// Recieves signal from menu.c (may implement level selector in future)
// Initializes level, level(n), player, environment, coins, constants, enemy, and more
// Receives signals from level.c to initialize levels (initLevels();)

#include "cprocessing.h"
#include "game.h"
#include "player.h"
#include "level.h"

// Define constants
const int num_levels = 5;

void init_game(Player* player) {
    initLevel(player, 0, NULL); // Initialize Level 0
}

void update_game(Player* player) {
    // Update the current level
    changeLevel(player->currentLevel, player);
    winCondition(player);
}

void draw_game(Player* player) {
    // Draw the current level
    drawLevel(player->currentLevel, player);
}

void escape_game() {
    // Clean up resources and exit the game
}
