//---------------------------------------------------------
// file:	game.h
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
#pragma once

#include "cprocessing.h"
#include "constants.h"
#include "player.h"
#include "level0.h"

// Define constants
typedef enum TileType TileType;

// Constants

// Room Layout

// Function prototypes
void returnScreenWidth();
void returnScreenHeight();
void init_game(PlayerLevel);
void shiftLevel(PlayerLevel);
void update_game();
void draw_game();
//void handle_input_game();
//void check_collisions_game();
void escape_game();
