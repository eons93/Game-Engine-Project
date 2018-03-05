#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"

void Level::loadMaps()
{
	//Playground Map
	{
		// Prep Textures
		if (!playground.bgImage.loadFromFile("Sprites/Backgrounds/Skyline.jpg"))
		{
			std::cout << "Background Image Failed to load" << std::endl;
		}
		if (!playground.levelImage.loadFromFile("Sprites/Backgrounds/Playground.png"))
		{
			std::cout << "Level Image Failed to load" << std::endl;
		}

		playground.CollisionData.resize(MAXCOLLISIONS);
		playground.SlopeData.resize(MAXSLOPES);
		playground.PlatformData.resize(MAXPLATFORMS);
		
		// Spawn Location
		playground.playerSpawn.x = bitConvert64(15.5);
		playground.playerSpawn.y = bitConvert64(15);

		


		// Floor Collisions -- RED
		playground.CollisionData[0].InitializeCollision(FLOOR, true, sf::Vector2f(0, 20), sf::Vector2f(28, 0));
		playground.CollisionData[1].InitializeCollision(FLOOR, true, sf::Vector2f(28, 24), sf::Vector2f(22, 0));
		playground.CollisionData[2].InitializeCollision(FLOOR, true, sf::Vector2f(36, 19), sf::Vector2f(2, 0));
		playground.CollisionData[3].InitializeCollision(FLOOR, true, sf::Vector2f(42, 18), sf::Vector2f(4, 0));
		playground.CollisionData[4].InitializeCollision(FLOOR, true, sf::Vector2f(25, 19), sf::Vector2f(3, 0));
		playground.CollisionData[5].InitializeCollision(FLOOR, true, sf::Vector2f(42, 13), sf::Vector2f(4, 0));
		


		// Left Collisions -- GREEN
		playground.CollisionData[24].InitializeCollision(LEFT_WALL, true, sf::Vector2f(4, 4), sf::Vector2f(0, 16));
		playground.CollisionData[25].InitializeCollision(LEFT_WALL, true, sf::Vector2f(28, 20), sf::Vector2f(0, 4));
		playground.CollisionData[26].InitializeCollision(LEFT_WALL, true, sf::Vector2f(38, 19), sf::Vector2f(0, 5));

		// Right Collisions -- BLUE
		
		playground.CollisionData[49].InitializeCollision(RIGHT_WALL, true, sf::Vector2f(36, 19), sf::Vector2f(0, 5));
		playground.CollisionData[50].InitializeCollision(RIGHT_WALL, true, sf::Vector2f(46, 0), sf::Vector2f(0, 24));
		playground.CollisionData[51].InitializeCollision(RIGHT_WALL, true, sf::Vector2f(42, 18), sf::Vector2f(0, 1));
		playground.CollisionData[52].InitializeCollision(RIGHT_WALL, true, sf::Vector2f(42, 13), sf::Vector2f(0, 1));

		// Ceiling Collisions -- YELLOW
		
		playground.CollisionData[74].InitializeCollision(CEILING, true, sf::Vector2f(42, 19), sf::Vector2f(4, 0));
		playground.CollisionData[75].InitializeCollision(CEILING, true, sf::Vector2f(42, 14), sf::Vector2f(4, 0));
		playground.CollisionData[76].InitializeCollision(CEILING, true, sf::Vector2f(4, 4), sf::Vector2f(42, 0));


		// Platform Collisions
		playground.PlatformData[0].InitializePlatform(sf::Vector2f(34, 21), sf::Vector2f(2, .25));
		playground.PlatformData[1].InitializePlatform(sf::Vector2f(38, 21), sf::Vector2f(2, .25));
		playground.PlatformData[2].InitializePlatform(sf::Vector2f(34, 15), sf::Vector2f(6, .25));
		playground.PlatformData[3].InitializePlatform(sf::Vector2f(38, 10), sf::Vector2f(3, .25));
		playground.PlatformData[4].InitializePlatform(sf::Vector2f(6, 7), sf::Vector2f(31, .25));


		// Slope Collisions
		playground.SlopeData[0].InitializeSlope(RIGHT, false, sf::Vector2f(23, 19), sf::Vector2f(2, 1));
		playground.SlopeData[1].InitializeSlope(LEFT, false, sf::Vector2f(28, 19), sf::Vector2f(1, 1));
		playground.SlopeData[2].InitializeSlope(LEFT, false, sf::Vector2f(29, 20), sf::Vector2f(1, 1));
		playground.SlopeData[3].InitializeSlope(LEFT, false, sf::Vector2f(30, 21), sf::Vector2f(1, 1));
		playground.SlopeData[4].InitializeSlope(LEFT, false, sf::Vector2f(31, 22), sf::Vector2f(1, 1));
		playground.SlopeData[5].InitializeSlope(LEFT, false, sf::Vector2f(32, 23), sf::Vector2f(1, 1));

	
	
		
		
	}
}