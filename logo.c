//---------------------------------------------------------
// File:    logo.c
// Author:  [NAME]
// Email:   [DIGIPEN EMAIL ADDRESS]
// Brief:   Template file for holding gamestate functions.
//
// Documentation Link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen. All rights reserved.
//---------------------------------------------------------


// LOGO
// Displays the DigiPen Logo when the program starts for 2 sec
// 1 second of cool animation
// Shifts you to the game menu

#include "cprocessing.h"
#include "logo.h"
#include "menu.h"
#include "constants.h"

// Global Variables
CP_Image DigipenLogo;  // Image of DigiPen logo
float elapsedTime = 0.0f;  // Time elapsed since the start of the logo state

// Initializes the logo game state
void init_logo(void)
{
    // Initialize elapsed time and get screen dimensions
    elapsedTime = 0.0f;

    // Set window size to screen dimensions
    CP_System_SetWindowSize(screenWidth, screenHeight);

    // Load DigiPen logo image
    DigipenLogo = CP_Image_Load("./Assets/DigiPen_WHITE.png");
}

// Updates the logo game state
void update_logo(void)
{
    // Clear the background
    CP_Graphics_ClearBackground(CP_Color_Create(30, 30, 30, 255));

    // Get screen dimensions
    float rectPosX = CP_System_GetDisplayWidth() * 1.0f;
    float rectPosY = CP_System_GetDisplayHeight() * 1.0f;

    // Background color for DigiPen logo
    CP_Color backgroundColor3 = CP_Color_Create(17, 115, 56, 255);

    // Increment elapsed time
    elapsedTime += CP_System_GetDt();

    // Display DigiPen logo for first 2 seconds
    if (CP_System_GetSeconds() < 2.0f) {
        CP_Graphics_ClearBackground(backgroundColor3);
        CP_Image_Draw(DigipenLogo, rectPosX / 2.0f, rectPosY / 2.0f, 1026.0f, 249.0f, 255);
        return;
    }
    // Fade out the logo from 2nd to 3rd second
    else if (CP_System_GetSeconds() > 2.0f && CP_System_GetSeconds() < 3.0f) {
        CP_Graphics_ClearBackground(backgroundColor3);

        // Calculate fade amount and scale factor
        float fadeAmount = 254.0f - 255.0f * (elapsedTime / 4.0f);
        if (fadeAmount < 0.0f) {
            fadeAmount = 0.0f;
        }
        float scaleFactor = 2.0f - ((elapsedTime / 1.0f) * 1.0f);
        float width = (1026.0f / scaleFactor);
        float height = 249.0f / scaleFactor;

        // Draw logo with advanced settings
        CP_Image_DrawAdvanced(DigipenLogo, rectPosX * 0.5f, rectPosY * 0.5f, width, height, (int)fadeAmount, (float)fadeAmount * 7.0f / (CP_System_GetSeconds() / 1.0f));
        return;
    }
    // After 3 seconds, switch to the menu game state
    else {
        CP_Color programColor = CP_Color_Create(150, 240, 250, 255);
        CP_Graphics_ClearBackground(programColor);
    }

    if (CP_System_GetSeconds() > 3.0f) {
        CP_Engine_SetNextGameState(init_menu, update_menu, exit_menu);
    }
}

// Cleans up resources used by the logo game state
void exit_logo(void)
{
    CP_Image_Free(&DigipenLogo); // Free memory allocated for the logo image
}
