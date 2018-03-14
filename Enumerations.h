#pragma once
#include <SFML\Graphics.hpp>

#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

enum EnemyType
{
	ET_ELITE,
	ET_GRUNT
};

enum PlatformType
{
	PT_CEILING,
	PT_FLOOR,
	PT_LEFT_WALL,
	PT_RIGHT_WALL,
	PT_PLATFORM
};

enum ComplexState
{
	CS_GROUND_FACE,
	CS_GROUND_MOVING,
	CS_GROUND_SHOOT,
	CS_GROUND_MELEE,
	CS_JUMP,
	CS_DUCK,
	CS_ROLL,
	CS_BLOCK,
	CS_AIR,
	CS_AIR_SHOOT,
	CS_AIR_MELEE
};

enum AIState
{
	PATROL,
	CHASE,
	ATTACK,
	DEFEND,
	PROTECT,
	FLEE
};

enum moveType
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};

#endif