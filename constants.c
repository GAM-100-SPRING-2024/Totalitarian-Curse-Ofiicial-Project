//---------------------------------------------------------
// file:	constants.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	header file for template gamestate
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include "constants.h"
#include <windows.h>

// CONSTANTS
// 
// Holds important grid-related constants
// Used by nearly every file once the level begins
// Could be used later for other important constants

int screenWidth;
int screenHeight;
const float gridRows = 27.f;
const float gridCols = 48.f;
float tileHeight;
float tileWidth;

void GetMonitorResolution() {
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    const float tileWidth = screenWidth / 48.0f;
    const float tileHeight = screenHeight / 27.0f;
}

