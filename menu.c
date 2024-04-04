///---------------------------------------------------------
// File:    menu.c
// Author:  [NAME]
// Email:   [DIGIPEN EMAIL ADDRESS]
// Brief:   Template file for holding gamestate functions.
//
// Documentation Link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen. All rights reserved.
//---------------------------------------------------------

// MENU
// Creates the Game Main Menu
// Allows you to Start Game and Quit
// May include level navigation *far future
// Will create settings tab and file *future

#include "cprocessing.h"
#include "menu.h"
#include "game.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>



//Text Alignment
CP_TEXT_ALIGN_HORIZONTAL horizontal;    // Horizontal alignment for text
CP_TEXT_ALIGN_VERTICAL vertical;        // Vertical alignment for text

// Function to check if mouse is over a rectangle
int IsMouseOverRectangle(float mouseX, float mouseY, float rectX, float rectY, float rectileWidth, float rectileHeight)
{
    // Check if mouse button is released
    int mousePressed = CP_Input_MouseReleased(MOUSE_BUTTON_LEFT);

    // Check if mouse is within rectangle and mouse button is pressed
    if (mouseX >= rectX - rectileWidth / 2 && mouseX <= rectX + rectileWidth / 2 &&
        mouseY >= rectY - rectileHeight / 2 && mouseY <= rectY + rectileHeight / 2 &&
        mousePressed)
    {
        return 1; // Mouse is over rectangle and pressed
    }
    return 0; // Mouse is not over rectangle or not pressed
}

// Initializes the menu creation
void init_menu(void)
{
    // Get screen dimensions and set window size
    GetMonitorResolution();
    CP_System_SetWindowSize(screenWidth, screenHeight);

    // Set text alignment and size
    horizontal = CP_TEXT_ALIGN_H_CENTER;
    vertical = CP_TEXT_ALIGN_V_MIDDLE;
    CP_Settings_TextSize(100);
    CP_Settings_RectMode(CP_POSITION_CENTER); // Set shape coordinates to center
}

// Updates the menu in real time
void update_menu(void)
{
    // Set background color
    CP_Graphics_ClearBackground(CP_Color_Create(70, 70, 60, 255));
    CP_Color startColor = CP_Color_Create(20, 100, 150, 255);
    CP_Settings_Fill(startColor);

    // Calculate button positions relative to screen dimensions
    float titleWidth = screenWidth / 2.0f;
    float titleHeight = screenHeight / 6.0f;
    float titleX = screenWidth / 2.0f;
    float titleY = screenHeight / 2.0f - 700.0f;
    float buttonWidth = screenWidth / 4.2f;
    float buttonHeight = screenHeight / 8.0f;
    float startGameButtonX = screenWidth / 2.0f;
    float startGameButtonY = screenHeight / 2.0f - 200.0f;
    float quitButtonX = screenWidth / 2.0f;
    float quitButtonY = screenHeight / 2.0f + 200.0f;

    // Draw title and buttons
    CP_Graphics_DrawRect(titleX, titleY, titleWidth, titleHeight);
    CP_Graphics_DrawRect(startGameButtonX, startGameButtonY, buttonWidth, buttonHeight);
    CP_Graphics_DrawRect(quitButtonX, quitButtonY, buttonWidth, buttonHeight);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(160.0f); // Increase text size
    CP_Font_DrawText("Totalitarian Curse", titleX - 280.0f, titleY + 60.f);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(80.0f); // Increase text size
    CP_Font_DrawText("Start Game", startGameButtonX - 160.0f, startGameButtonY + 20.f);
    CP_Font_DrawText("Quit", quitButtonX - 80.0f, quitButtonY + 20.f);

    // Check for mouse click events
    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
        float mouseX = CP_Input_GetMouseX();
        float mouseY = CP_Input_GetMouseY();

        // Check if Start Game button is clicked
        if (IsMouseOverRectangle(mouseX, mouseY, startGameButtonX, startGameButtonY, buttonWidth, buttonHeight))
        {
            CP_Engine_SetNextGameState(init_game, update_game, exit);
        }

        // Settings button will be implemented here in the future
        /*
        if (IsMouseOverRectangle(mouseX, mouseY, startGameButtonX, startGameButtonY, buttonWidth, buttonHeight))
        {
            CP_Engine_SetNextGameState(init_settings, update_settings, exit_settings);
        }
        */

        //
        
        // Check if Quit button is clicked
        else if (IsMouseOverRectangle(mouseX, mouseY, quitButtonX, quitButtonY, buttonWidth, buttonHeight))
        {
            CP_Engine_Terminate();
        }
    }
}

// Cleans up resources used by the menu game state
void exit_menu(void)
{
    // Clean up assets if used in the future
}
