//Creates the player

//Headers
#include "cprocessing.h"
#include "constants.h"
#include "game.h"
#include "environment.h"
#include "level0.h"
#include "player.h"
#include "platform.h"
#include <math.h>

// PLATFORM
// Receives tile information and function from environment.c
// Utilizes drawTileSequence function to create many tile groups
// 
// 
// NO LONGER USED FOR THIS, WILL BE HANDLED BY ENVIRONMENT.C
// Checks for collision between player and platform
// Prevents player movement / hurts player
// Checks for enemy collision with platform *future
// Stops ranged attacks *far future
// Tile groups will be combined in specific level files and defined into functions
// 
// 
// Platforms layouts will be initialized in levels.c
// Objects will be initialized by game.c

// PLATFORM TEMPLATES

// LEVEL 0
// This function spawns tiles in rows and columns.
// You can use it to customize features, such as cliffs,
// Will be used to create templates in levels(n).c, which will be declared in level.c
void generatePlatform(float x, float y, int width, int height, TileType type) {
    // Loop through each row and column to spawn tiles
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Generate tile based on the specified type
            generateTile(x + j, y - i, 1, 1, type);
        }
    }
}

//  || LAYOUTS ||

// LEVEL 0

// Function to place platforms for room 1
void placePlatform001() {
    // Example platform 1
    generatePlatform(13, 22, 4, 2, Stone); 
    generatePlatform(20, 19, 3, 1, Wood); 
    generatePlatform(8, 15, 2, 1, Stone); 
}

// Function to place platforms for room 2
void placePlatform002() {
    // Example platform 2
    generatePlatform(13, 22, 4, 2, Stone); 
    generatePlatform(20, 19, 3, 1, Wood); 
    generatePlatform(8, 15, 2, 1, Stone); 
}

// Function to place platforms for room 3
void placePlatform003() {
    // Example platform 3
    generatePlatform(13, 22, 4, 2, Stone); 
    generatePlatform(20, 19, 3, 1, Wood); 
    generatePlatform(8, 15, 2, 1, Stone); 
}

// Function to place platforms for room 4
void placePlatform004() {
    // Example platform 4
    generatePlatform(13, 22, 4, 2, Stone); 
    generatePlatform(20, 19, 3, 1, Wood); 
    generatePlatform(8, 15, 2, 1, Stone); 
}




















/*

#define jump_speed_initial -700.0f
#define gravity_initial 9.8f * 20.0f
#define max_jump_height 300.0f
#define jump_decay_factor 0.5f

Character Player;

extern float gravity;

void spawnPlayer(float spawnX, float spawnY) {
    Player.posX = spawnX;
    Player.posY = spawnY;
    Player.radius = 20.0f; // Adjust as needed
    Player.isJumping = 0;
    Player.groundHeight = 0.0f;
    Player.jumpSpeed = 0.0f;
    Player.jumpElapsedTime = 0.0f;
    Player.jumpTime = 0.0f;
    Player.CharColor = CP_Color_Create(255, 0, 0, 255); // Red color for player
}

void updateJump(float dt) {
    if (Player.isJumping) {
        Player.jumpSpeed += gravity * dt;

        if (Player.jumpSpeed >= 0) {
            Player.jumpSpeed *= jump_decay_factor;
        }

        Player.posY += Player.jumpSpeed * dt;

        if (Player.posY >= Player.groundHeight) {
            Player.posY = Player.groundHeight;
            Player.isJumping = 0;
            Player.jumpSpeed = 0;
        }
    }
}

void jump() {
    if (!Player.isJumping) {
        Player.isJumping = 1;
        Player.jumpSpeed = jump_speed_initial;
        Player.groundHeight = Player.posY;
    }
}

void move(int stop) {
    // Movement logic for left and right
    // Implement according to your requirements
    float movementSpeed = 200.0f; // Adjust as needed
    if (stop != 2) {
        if (CP_Input_KeyDown(KEY_A)) {
            Player.posX -= movementSpeed * CP_System_GetDt();
        }
    }
    if (stop != 1) {
        if (CP_Input_KeyDown(KEY_D)) {
            Player.posX += movementSpeed * CP_System_GetDt();
        }
    }
}

int hitGround(GroundData grounds[])
{
    for (int i = 0; i < GroundCount; i++) {
        if (Player.posX < grounds[i].posX + grounds[i].width &&
            Player.posX + Player.radius > grounds[i].posX &&
            Player.posY < grounds[i].posY + grounds[i].height &&
            Player.posY + Player.radius > grounds[i].posY)
        {
            return 1;
        }
    }
    return 0;
}

int hitWall(GroundData walls[])
{
    for (int i = 0; i < wallCount; i++) {
        if (Player.posX < walls[i].posX + walls[i].width &&
            Player.posX + Player.radius > walls[i].posX &&
            Player.posY < walls[i].posY + walls[i].height &&
            Player.posY + Player.radius > walls[i].posY)
        {
            return 1;
        }
    }
    return 0;
}

void airMove(int stop) {
    // Air movement logic
    float movementSpeed = 350.0f; // Adjust as needed
    if (stop != 2) {
        if (CP_Input_KeyDown(KEY_A)) {
            Player.posX -= movementSpeed * CP_System_GetDt();
        }
    }
    if (stop != 1) {
        if (CP_Input_KeyDown(KEY_D)) {
            Player.posX += movementSpeed * CP_System_GetDt();
        }
    }
    if (stop == 4) {
        Player.isJumping = 0;
        Player.jumpElapsedTime = 0;
    }
}

void CharacterMovement(GroundData grounds[], GroundData walls[]) {
    float jumpSpeed = 800.0f; // Adjust as needed

    if (hitGround(grounds) == 0 && hitWall(walls) != 3 && Player.isJumping == 0) {
        gravity = gravity_initial;
        airMove(hitWall(walls));
    }
    else if (hitGround(grounds) == 1 || hitWall(walls) != 0) {
        gravity = 0.0f;
        airMove(hitWall(walls));

        if (CP_Input_KeyTriggered(KEY_W) && hitWall(walls) != 0) {
            Player.isJumping = 1;
        }
        else if (CP_Input_KeyTriggered(KEY_W) && hitGround(grounds) == 1) {
            Player.isJumping = 1;
        }
        else {
            Player.isJumping = 0;
        }

    }
    else {
        gravity = 0;
        airMove(0);
    }

    if (Player.isJumping == 1) {
        Player.jumpTime = 0.3f;
        if (Player.jumpElapsedTime < Player.jumpTime) {
            Player.jumpElapsedTime += 1.0f * CP_System_GetDt();
            Player.posY -= jumpSpeed * CP_System_GetDt();
        }
        else {
            Player.jumpElapsedTime = 0;
            Player.isJumping = 0;
        }

    }

    Player.posY += gravity * CP_System_GetDt();
    CP_Settings_Fill(Player.CharColor);
    CP_Graphics_DrawCircle(Player.posX, Player.posY, Player.radius);
}

*/