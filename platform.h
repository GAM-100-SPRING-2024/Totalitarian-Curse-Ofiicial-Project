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


//Declares player functions

#pragma once
#include "game.h"
#include "level0.h"
#include "cprocessing.h"
#include "player.h"

// Define the Platform struct
typedef struct {
	float x;
	float y;
	float width;
	float height;
} Platform;

// Function prototypes
void generatePlatform(float x, float y, int width, int height, TileType type);
void placePlatform001(Platform* platform);
void placePlatform002(Platform* platform);
void placePlatform003(Platform* platform);
void placePlatform004(Platform* platform);
















/*
typedef struct
{
	float posX;
	float posY;
	float radius;
	CP_Color CharColor;
	float jumpSpeed;
	float groundHeight;
	int isJumping;
	float jumpElapsedTime;
	float jumpTime;
} Character;

extern Character Player;
extern float gravity;

void updateJump(float dt);
void jump();
void move(int stop);
int hitGround(GroundData grounds[]);
int hitWall(GroundData walls[]);
void airMove(int stop);
void CharacterMovement(GroundData grounds[], GroundData walls[]);
*/
