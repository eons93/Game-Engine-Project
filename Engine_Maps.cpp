#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"
#include "Engine.h"

void Engine::LoadMaps()
{
	//Playground Map
	{
		// Prep Textures
		if (!map_TestChamber.txu_BackgroundImage.loadFromFile("Sprites/Backgrounds/Skyline.jpg"))
		{
			std::cout << "Background Image Failed to load" << std::endl;
		}
		if (!map_TestChamber.txu_LevelImage.loadFromFile("Sprites/Backgrounds/Playground.png"))
		{
			std::cout << "Level Image Failed to load" << std::endl;
		}

		map_TestChamber.col_CollisionData.resize(MAXCOLLISIONS);
		map_TestChamber.slo_SlopeData.resize(MAXSLOPES);
		map_TestChamber.pla_PlatformData.resize(MAXPLATFORMS);
		map_TestChamber.et_EnemyData.resize(MAXENEMIES);
		map_TestChamber.vec_EnemySpawn.resize(MAXENEMIES);

		
		// Spawn Location
		map_TestChamber.vec_PlayerSpawn.x = BitConvert64(16.5);
		map_TestChamber.vec_PlayerSpawn.y = BitConvert64(19);

		// Enemy Information
		map_TestChamber.int_NumEnemies = 3;
		
		map_TestChamber.et_EnemyData[0] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[0].x = BitConvert64(4.5);
		map_TestChamber.vec_EnemySpawn[0].y = BitConvert64(15);

		map_TestChamber.et_EnemyData[1] = ET_ELITE;
		map_TestChamber.vec_EnemySpawn[1].x = BitConvert64(6.5);
		map_TestChamber.vec_EnemySpawn[1].y = BitConvert64(15);

		map_TestChamber.et_EnemyData[2] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[2].x = BitConvert64(8.5);
		map_TestChamber.vec_EnemySpawn[2].y = BitConvert64(15);

		map_TestChamber.et_EnemyData[3] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[3].x = BitConvert64(10.5);
		map_TestChamber.vec_EnemySpawn[3].y = BitConvert64(15);

		map_TestChamber.et_EnemyData[4] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[4].x = BitConvert64(12.5);
		map_TestChamber.vec_EnemySpawn[4].y = BitConvert64(15);
		

		// Floor Collisions -- RED
		map_TestChamber.col_CollisionData[0].InitializeCollision(PT_FLOOR, true, sf::Vector2f(0, 20), sf::Vector2f(28, 0));
		map_TestChamber.col_CollisionData[1].InitializeCollision(PT_FLOOR, true, sf::Vector2f(28, 24), sf::Vector2f(22, 0));
		map_TestChamber.col_CollisionData[2].InitializeCollision(PT_FLOOR, true, sf::Vector2f(36, 19), sf::Vector2f(2, 0));
		map_TestChamber.col_CollisionData[3].InitializeCollision(PT_FLOOR, true, sf::Vector2f(42, 18), sf::Vector2f(4, 0));
		map_TestChamber.col_CollisionData[4].InitializeCollision(PT_FLOOR, true, sf::Vector2f(25, 19), sf::Vector2f(3, 0));
		map_TestChamber.col_CollisionData[5].InitializeCollision(PT_FLOOR, true, sf::Vector2f(42, 13), sf::Vector2f(4, 0));
		
		// Left Collisions -- GREEN
		map_TestChamber.col_CollisionData[24].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(4, 4), sf::Vector2f(0, 16));
		map_TestChamber.col_CollisionData[25].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(28, 20), sf::Vector2f(0, 4));
		map_TestChamber.col_CollisionData[26].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(38, 19), sf::Vector2f(0, 5));

		// Right Collisions -- BLUE
		map_TestChamber.col_CollisionData[49].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(36, 19), sf::Vector2f(0, 5));
		map_TestChamber.col_CollisionData[50].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(46, 0), sf::Vector2f(0, 24));
		map_TestChamber.col_CollisionData[51].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(42, 18), sf::Vector2f(0, 1));
		map_TestChamber.col_CollisionData[52].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(42, 13), sf::Vector2f(0, 1));

		// Ceiling Collisions -- YELLOW
		map_TestChamber.col_CollisionData[74].InitializeCollision(PT_CEILING, true, sf::Vector2f(42, 19), sf::Vector2f(4, 0));
		map_TestChamber.col_CollisionData[75].InitializeCollision(PT_CEILING, true, sf::Vector2f(42, 14), sf::Vector2f(4, 0));
		map_TestChamber.col_CollisionData[76].InitializeCollision(PT_CEILING, true, sf::Vector2f(4, 4), sf::Vector2f(42, 0));

		// Platform Collisions
		map_TestChamber.pla_PlatformData[0].InitializePlatform(sf::Vector2f(34, 21), sf::Vector2f(2, .25));
		map_TestChamber.pla_PlatformData[1].InitializePlatform(sf::Vector2f(38, 21), sf::Vector2f(2, .25));
		map_TestChamber.pla_PlatformData[2].InitializePlatform(sf::Vector2f(34, 15), sf::Vector2f(6, .25));
		map_TestChamber.pla_PlatformData[3].InitializePlatform(sf::Vector2f(38, 10), sf::Vector2f(3, .25));
		map_TestChamber.pla_PlatformData[4].InitializePlatform(sf::Vector2f(6, 7), sf::Vector2f(31, .25));

		// Slope Collisions
		map_TestChamber.slo_SlopeData[0].InitializeSlope(RIGHT, false, sf::Vector2f(23, 19), sf::Vector2f(2, 1));
		map_TestChamber.slo_SlopeData[1].InitializeSlope(LEFT, false, sf::Vector2f(28, 19), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[2].InitializeSlope(LEFT, false, sf::Vector2f(29, 20), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[3].InitializeSlope(LEFT, false, sf::Vector2f(30, 21), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[4].InitializeSlope(LEFT, false, sf::Vector2f(31, 22), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[5].InitializeSlope(LEFT, false, sf::Vector2f(32, 23), sf::Vector2f(1, 1));
	}
}