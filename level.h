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
#include "player.h"
#include "level0.h"
#include "coins.h"
#include "constants.h"

// Constants

// Function prototypes

void initLevel(Player* player, int level, Coin* coins)
void update_game();
void drawLevel(int level, Player* player);
void updateLevel(int level, Player* player);
void winCondition(Player* player);

