// Include necessary headers
#include "cprocessing.h"
#include "constants.h"
#include "environment.h"
#include "groundLayout.h"

#include <stdio.h>

// Include necessary headers
#include "cprocessing.h"
#include "constants.h"
#include "environment.h"
#include "groundLayout.h"

#include <stdio.h>

// Forward declaration of functions

// Plains Room 1 & Room 2
void generatePlains1() {
    drawTileSequence(0, 22, 1, 48, Grass);
    drawTileSequence(0, 23, 2, 48, Soil);
    drawTileSequence(0, 25, 2, 48, Stone);
}

// Plains Room 3
void generatePlains2() {
    drawTileSequence(0, 22, 1, 27, Sand);
    drawTileSequence(0, 23, 2, 27, Sand);
    drawTileSequence(0, 25, 2, 27, Stone);

    //Creates Water
    drawTileSequence(24, 22, 5, 21, Water);
}

void generatePlains3() {

    drawTileSequence(0, 22, 5, 12, Water);
    drawTileSequence(13, 22, 5, 2, Snow);
    drawTileSequence(16, 22, 5, 32, Water);
}

// Function to generate Plains room 5
void generatePlains4() {
    drawTileSequence(0, 22, 1, 22, Snow);
    drawTileSequence(0, 23, 2, 22, Soil);
    drawTileSequence(0, 25, 2, 22, Stone);
    // Creates a void of 2 blocks
    drawTileSequence(24, 22, 5, 12, Stone);
    drawTileSequence(36, 22, 5, 6, Lava);
    // Small pool of water above stone
    drawTileSequence(42, 21, 6, 1, Stone);
    drawTileSequence(43, 24, 3, 3, Stone);
    drawTileSequence(43, 22, 3, 2, Water);
    drawTileSequence(46, 22, 5, 2, Stone);

}

