#include "cprocessing.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//      STRUCTS

// Tile Names
// Will be added to other functions to create different properties
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

// Tile Feature Variables
typedef struct {
    int risk;
    int viscosity;
    int friction;
} TileInfo;


typedef struct {
    CP_Color baseColor;
    CP_Color detailColor;
    float x1, x2, y1, y2, y3; // Line coordinates
} TileDetails;


// Base Project Functions

void init_environment(void);
// Function to define tile types and their details
void tileTypes(TileType type, TileInfo* info, TileDetails* details);
void tileTypeProperties(float x, float y, TileType type, TileInfo* info, TileDetails* details);
TileDetails drawTileLines(TileType type, TileDetails* details, float x, float y, float tileWidth, float tileHeight);
void generateTile(float x, float y, float tileWidth, float tileHeight, TileType type);
void drawTileSequence(float startX, float startY, int gridRows, int gridCols, TileType type);

//Template functions
