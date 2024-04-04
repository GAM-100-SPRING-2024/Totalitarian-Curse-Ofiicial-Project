#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "cprocessing.h"
#include "environment.h"
#include "level0.h"
#include "constants.h"

// ENVIRONMENT
// 
// Defines blocks and their details
// Creates functions to spawn blocks
// Creates ground block templates, like cliffs, gaps, flat ground
// Handles ground based collisions
// Platforms & collisions handled by platform.c
// Templates will be used in level files to create room templates
// Block layouts and block spawing handled by level.c

//      STRUCTS



// TILE NAMES
// Interacts with other functions to create different properties
typedef enum {
    Grass,
    Soil,
    Stone,
    Wood,
    Sand,
    Snow,
    Water,
    Lava
} TileType;

// Tile Properties (for player)
typedef struct {
    int risk;
    int viscosity;
    int friction;
} TileInfo;

// Tile Illustration (for templates)
typedef struct {
    CP_Color baseColor;
    CP_Color detailColor;
    float x1, x2, y1, y2, y3; // Line coordinates
} TileDetails;


// PROGRAM BEGINS
//
// Sky is initialized (placeholder)
void init_environment(void)
{   
    GetMonitorResolution();
    CP_Color skyColor = CP_Color_Create(0, 0, 0, 255);
    CP_Graphics_ClearBackground(skyColor);
}

// Defines tile types and returns their details.
// Function to define tile types and their details
void tileTypes(TileType type, TileInfo* info, TileDetails* details) {
    tileTypeDetails(0, 0, type, info, details);
}


//This function contains the details to create different tile types
void tileTypeProperties(float x, float y, TileType type, TileInfo* info, TileDetails* details) {
    
    // BLOCK PROPERTIES
    // baseColor - color of the block itself
    // detailColor - color of the block's stroke (for lines inside block and block edges)
    // risk - the damage potential of the block
    // viscosity - the ability for the player to go through a block
    // friction - affects how fast you walk on blocks
    
    switch (type) {
        case Grass:
            //For level0, the grass will spawn on level 23
            details->baseColor = CP_Color_Create(50, 105, 56, 255); // Green
            details->detailColor = CP_Color_Create(10, 10, 20, 255); // Darker green
            info->risk = 0;         // No damage
            info->viscosity = 0;    // Player can't go through
            info->friction = 1;     // Normal friction
            break;
        case Soil:
            //Is the middle layer on ground level for level0 (Layer 24 and 25)
            details->baseColor = CP_Color_Create(70, 55, 26, 255); // Soil color
            details->detailColor = CP_Color_Create(20, 20, 20, 255); // Darker soil color
            info->risk = 0;         // No damage
            info->viscosity = 0;    // Player can't go through
            info->friction = 1;     // Normal friction
            break;
        case Stone:
            //Is the bottom layer on ground level for tutorial level (Layer 26 and 25) for level0
            details->baseColor = CP_Color_Create(128, 128, 128, 255); // Gray
            details->detailColor = CP_Color_Create(50, 50, 50, 255); // Dark gray
            info->risk = 0;         // No damage
            info->viscosity = 0;    // Player can't go through
            info->friction = 1;     // Normal friction
            break;
        case Wood:
            //Is the bottom layer on ground level for tutorial level (Layer 26 and 25) for level0
            details->baseColor = CP_Color_Create(210, 105, 230, 255); // Brown
            details->detailColor = CP_Color_Create(139, 69, 19, 255); // Dark brown
            info->risk = 0;         // No damage
            info->viscosity = 0;    // Player can't go through
            info->friction = 1;     // Normal friction
            break;
        case Sand:
            //Spawns on Level 3
            details->baseColor = CP_Color_Create(240, 155, 29, 255); // Sand color
            details->detailColor = CP_Color_Create(120, 60, 2, 255); // Darker sand color
            info->risk = 0;         // No damage
            info->viscosity = 0;    // Player can't go through
            info->friction = 2;     // Slower player speed
            break;
        case Snow:
            //Spawns on Level 1
            details->baseColor = CP_Color_Create(250, 245, 255, 255); // Snow color
            details->detailColor = CP_Color_Create(200, 190, 200, 255); // Darker snow color
            info->risk = 0;         // No damage
            info->viscosity = 0;    // Player can't go through
            info->friction = 0;     // Less friction (faster speed)
            break;
        case Water:
            //Spawns on all levels
            details->baseColor = CP_Color_Create(100, 125, 255, 255); // Water color
            details->detailColor = CP_Color_Create(40, 70, 200, 255); // Darker water color
            info->risk = 1;         // Damage if player remains for over 15 sec
            info->viscosity = 2;    // Player can go through water somewhat quickly
            info->friction = -1;     // Not considered
            break;
        case Lava:
            //Spawns on all Levels, injures player when touched
            details->baseColor = CP_Color_Create(250, 55, 15, 255); // Lava color
            details->detailColor = CP_Color_Create(160, 20, 0, 255); // Darker lava color
            info->risk = 2;         // Immediate damage upon contact, sustained damage for over 3 sec of contact
            info->viscosity = 1;    // Player can go through lava slowly
            info->friction = -1;     // Not considered
            break;

    }
}

// Function to draw lines for a tile based on its type
TileDetails drawTileLines(TileType type, TileDetails* details, float x, float y, float tileWidth, float tileHeight) {
    switch (type) {
        case Grass:
            // Define grass line coordinates
            details->x1 = x + tileWidth / 4.0f;
            details->x2 = x + 3.0f * tileWidth / 4.0f;
            details->y1 = y + tileHeight / 2.0f;
            details->y2 = y + tileHeight / 4.0f;
            details->y3 = y + 3.0f / 4.0f;
            break;

        case Soil:
            // Define soil line coordinates
            details->x1 = x + tileWidth / 4.0f;
            details->x2 = x + 3.0f * tileWidth / 4.0f;
            details->y1 = y + tileHeight / 2.0f;
            details->y2 = y + tileHeight / 4.0f;
            details->y3 = y + 3.0f / 4.0f;
            break;

        case Stone:
            // Define stone line coordinates
            details->x1 = x + tileWidth / 4.0f;
            details->x2 = x + 3.0f * tileWidth / 4.0f;
            details->y1 = y + tileHeight / 2.0f;
            details->y2 = y + tileHeight / 4.0f;
            details->y3 = y + 3.0f / 4.0f;
            break;

        case Wood:
            // Define wood line coordinates
            details->x1 = x + tileWidth / 4.0f;
            details->x2 = x + 3.0f * tileWidth / 4.0f;
            details->y1 = y + tileHeight / 2.0f;
            details->y2 = y + tileHeight / 4.0f;
            details->y3 = y + 3.0f / 4.0f;
            break;

         case Sand:
            details->x1 = x + tileWidth / 4.0f;
            details->x2 = x + 3.0f * tileWidth / 4.0f;
            details->y1 = y + tileHeight / 2.0f;
            details->y2 = y + tileHeight / 4.0f;
            details->y3 = y + 3.0f / 4.0f;
            break;

         case Snow:
             details->x1 = x + tileWidth / 4.0f;
             details->x2 = x + 3.0f * tileWidth / 4.0f;
             details->y1 = y + tileHeight / 2.0f;
             details->y2 = y + tileHeight / 4.0f;
             details->y3 = y + 3.0f / 4.0f;
             break;

         case Water:
             details->x1 = x + tileWidth / 4.0f;
             details->x2 = x + 3.0f * tileWidth / 4.0f;
             details->y1 = y + tileHeight / 2.0f;
             details->y2 = y + tileHeight / 4.0f;
             details->y3 = y + 3.0f / 4.0f;
             break;

         case Lava:
             details->x1 = x + tileWidth / 4.0f;
             details->x2 = x + 3.0f * tileWidth / 4.0f;
             details->y1 = y + tileHeight / 2.0f;
             details->y2 = y + tileHeight / 4.0f;
             details->y3 = y + 3.0f / 4.0f;
             break;

    }
}

// Generates a single tile with properties and details
void generateTile(float x, float y, float tileWidth, float tileHeight, TileType type) {
    TileInfo info;
    TileDetails details;

    // Obtain properties and details for a given tile
    tileTypeProperties(x, y, type, &info, &details);
    // Draw tile shape
    CP_Settings_Fill(details.baseColor);
    CP_Settings_Stroke(details.detailColor);
    CP_Graphics_DrawRect(x, y, tileWidth, tileHeight);

    // Draw lines for the tile based on its type
    drawTileLines(type, &details, x, y, tileWidth, tileHeight);
    CP_Graphics_DrawLine(details.x1, details.y1, details.x2, details.y1); // horizontal line
    CP_Graphics_DrawLine(details.x1, details.y2, details.x1, details.y3); // left vertical line
    CP_Graphics_DrawLine(details.x2, details.y2, details.x2, details.y3); // right vertical line
}

// This function spawns tiles in rows and columns. 
// You can use it to customize features, such as cliffs, 
// Will be used to create templates in levels(n).c, which will be declared in level.c
void drawTileSequence(float startX, float startY, int gridRows, int gridCols, TileType type) {
    //Loop through each row and column to spawn tiles
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols; j++) {
            float x = startX + j *  gridRows;
            float y = startY + i * gridCols;

            //Generate tile based on the specified type
            generateTile(x, y, 1, 1, type);
        }
    }
}

// CHECKS ALL TILE COLLISIONS (Will need to be edited for enemy)
int check_collision(Player* player, float playerNextX, float playerNextY, TileInfo* tileInfo) {
    // Check collision between player and tile
    // Implement collision detection logic based on tile properties
    // Example: AABB collision detection with additional checks for tile properties

    // Calculate the player's bounding box
    float playerRight = playerNextX + player->size;
    float playerBottom = playerNextY + player->size;

    // Check each corner of the player's bounding box for collision with the tile
    if (tileInfo->viscosity == 0 && tileInfo->friction != -1 &&
        playerNextX < tileWidth && playerRight > 0 &&
        playerNextY < tileHeight && playerBottom > 0) {
        return 1; // Collision detected
    }

    // No collision
    return 0;
}



