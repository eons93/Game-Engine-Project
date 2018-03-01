#pragma once
#include <SFML\Graphics.hpp>

#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H



enum PlatformType
{
	CEILING,
	FLOOR,
	LEFT_WALL,
	RIGHT_WALL,
	PLATFORM
};

enum ComplexState
{
	GROUND_FACE,
	GROUND_MOVING,
	GROUND_SHOOT,
	GROUND_MELEE,
	C_JUMP,
	C_DUCK,
	C_ROLL,
	C_BLOCK,
	AIR,
	AIR_SHOOT,
	AIR_MELEE
};

enum moveType
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};

#endif