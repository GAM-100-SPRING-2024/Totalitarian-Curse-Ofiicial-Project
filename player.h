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
#include "cprocessing.h"
#include "game.h"
#include "environment.h"
#include "level0.h"
//#include "level1.h"
//#include "level2.h"
//#include "level3.h"
//#include "level4.h"
//Declares player functions

#pragma once

// Forward declared functions from other files:
typedef struct TileInfo TileInfo;

#define gravity 0.5f
#define jump_force 10.0f
#define move_speed 10.0f
#define swim_speed 5.0f
#define swim_upward_force 5.0f
#define water_gravity_multiplier 0.5f
#define lava_gravity_multiplier 2.0f
#define lava_speed_multiplier 0.5f


typedef struct {
	CP_Vector position;
	CP_Vector velocity;
	int width;
	int height;
	int size;
	int state;
	int health;
	int lives;
	int score;
	//CP_Image sprite;
	int lavaTimer;
	int waterTimer;
	int currentPlayerLevel;
	int currentPlayerRoom;
} Player;

typedef enum {
	idle,
	walking,
	jumping,
	crouching,
	inWater,
	inLava
} PlayerState;

//Current functions
void player_handle_input(Player* player);
void player_check_collisions(Player* player, TileInfo* tiles, int gridCols);
void player_update(Player* player);
void player_screen_collision(Player* player);
void player_respawn(Player* player);
void player_timer(Player* player, float dt);
















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
