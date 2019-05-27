#pragma once
#define TEX_STAGE31 1
#define TEX_STAGE32 2
#define TEX_STAGE33 3
#define TEX_PLAYER 4
#define TEX_SPARTA 5
#define TEX_CAT 6
#define TEX_THROWER 7
#define TEX_EAGLE 8
#define TEX_SOLDIER 9
#define TEX_HOLDER 10
#define TEX_ITEM 11

#define PLAYER_SLASH_FRAME 7
#define PLAYER_RUNNING_FRAME 4
#define PLAYER_JUMPING_FRAME 2
#define SPARTA_FRAME 15
#define CAT_FRAME 15
#define THROWER_FRAME 15
#define EAGLE_FRAME 15
#define SOLDIER_FOLLOW_FRAME 14
#define SOLDIER_ATTACK_FRAME 2
#define SOLDIER_ATTACK_PERCENTTIME 15
#define SOLDIER_FOLLOW_PERCENTTIME 2.5f
#define HOLDER_FRAME 10

#define GRID_ROWS 5
#define GRID_COLUMNS 5
#define PLAYER_RUN_VELOCITY 90
#define PLAYER_JUMP_ACCELERATEX 15
#define GRAVITY 12
#define PLAYER_MIN_JUMP_VELOCITY 270
#define PLAYER_MAX_FALLING_VELOCITY -270

#define SPARTA_SPEED 30.0f
#define THROWER_SPEED 30.0f
#define EAGLE_ACCELERATE 12.0f
#define CAT_SPEED 110.0f
#define CAT_JUMP_VELOCITY 120.0f
#define CAT_GRAVITY 10
#define SOLDIER_SPEED 30.0f

#define PLAYER_OFFSET_GROUND PLAYER_MIN_JUMP_VELOCITY * 1.0 / 60
#define ENEMY_OFFSET_BORDER 2

#define ATTACK_DISTANCE 24