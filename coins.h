//---------------------------------------------------------
// file:	gamestate_game.h
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
#include "player.h"

typedef struct {
	float coinX;
	float coinY;
	float radius;
	CP_Color coinColor;
	
} Coin;

void createCoin(Coin* coin, int tileX, int tileY);
void initCoinShape(Coin* coin);
void checkCoinCollision(Player* player, Coin* coins, int numCoins);
void placeCoins001(Coin* coins);
void placeCoins002(Coin* coins);
void placeCoins003(Coin* coins);
void placeCoins004(Coin* coins);

