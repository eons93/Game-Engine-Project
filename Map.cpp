#include "stdafx.h"
#include "Map.h"
#include "Level.h"
#include "Enumerations.h"
#include "Enemy.h"

Map::Map()
{
	int_LoadedCollision.resize(100);
	int_LoadedEnemies.resize(100);
}

void Map::CreatePlatform(int indexStart, PlatformObject platform)
{
	// Variables to increase readability
	float top = platform.vec_Position.y;
	float left = platform.vec_Position.x;
	float height = platform.vec_Size.y;
	float width = platform.vec_Size.x;

	col_CollisionData[indexStart].InitializeCollision(PT_FLOOR, true, sf::Vector2f(left, top), sf::Vector2f(width, 1));
	col_CollisionData[indexStart + 1].InitializeCollision(PT_CEILING, true, sf::Vector2f(left, top + height), sf::Vector2f(width, -1));
	col_CollisionData[indexStart + 2].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(left + width, top), sf::Vector2f(-1, height));
	col_CollisionData[indexStart + 3].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(left, top), sf::Vector2f(1, height));
}