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

		map_TestChamber.int_NumColl = 40;
		map_TestChamber.int_NumPlat = 5;
		map_TestChamber.int_NumSlop = 6;
		map_TestChamber.int_NumEnemies = 5;

		map_TestChamber.col_CollisionData.resize(MAXCOLLISIONS);
		map_TestChamber.slo_SlopeData.resize(MAXSLOPES);
		map_TestChamber.pla_PlatformData.resize(MAXPLATFORMS);
		map_TestChamber.et_EnemyData.resize(MAXENEMIES);
		map_TestChamber.vec_EnemySpawn.resize(MAXENEMIES);

		
		// Spawn Location
		map_TestChamber.vec_PlayerSpawn.x = X_64(16.5);
		map_TestChamber.vec_PlayerSpawn.y = X_64(19);

		// Enemy Information
		map_TestChamber.int_NumEnemies = 3;
		
		map_TestChamber.et_EnemyData[0] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[0].x = X_64(4.5);
		map_TestChamber.vec_EnemySpawn[0].y = X_64(15);

		map_TestChamber.et_EnemyData[1] = ET_ELITE;
		map_TestChamber.vec_EnemySpawn[1].x = X_64(6.5);
		map_TestChamber.vec_EnemySpawn[1].y = X_64(15);

		map_TestChamber.et_EnemyData[2] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[2].x = X_64(8.5);
		map_TestChamber.vec_EnemySpawn[2].y = X_64(15);

		map_TestChamber.et_EnemyData[3] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[3].x = X_64(10.5);
		map_TestChamber.vec_EnemySpawn[3].y = X_64(15);

		map_TestChamber.et_EnemyData[4] = ET_GRUNT;
		map_TestChamber.vec_EnemySpawn[4].x = X_64(12.5);
		map_TestChamber.vec_EnemySpawn[4].y = X_64(15);
		

		// Floor Collisions -- RED
		map_TestChamber.col_CollisionData[0].InitializeCollision(PT_FLOOR, true, sf::Vector2f(0, 20), sf::Vector2f(28, 1));
		map_TestChamber.col_CollisionData[1].InitializeCollision(PT_FLOOR, true, sf::Vector2f(28, 24), sf::Vector2f(22, 1));
		map_TestChamber.col_CollisionData[2].InitializeCollision(PT_FLOOR, true, sf::Vector2f(36, 19), sf::Vector2f(2, 1));
		map_TestChamber.col_CollisionData[3].InitializeCollision(PT_FLOOR, true, sf::Vector2f(42, 18), sf::Vector2f(4, 1));
		map_TestChamber.col_CollisionData[4].InitializeCollision(PT_FLOOR, true, sf::Vector2f(25, 19), sf::Vector2f(3, 1));
		map_TestChamber.col_CollisionData[5].InitializeCollision(PT_FLOOR, true, sf::Vector2f(42, 13), sf::Vector2f(4, 1));
		
		
		// Left Collisions -- GREEN
		map_TestChamber.col_CollisionData[6].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(4, 4), sf::Vector2f(-1, 16));
		map_TestChamber.col_CollisionData[7].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(28, 20), sf::Vector2f(-1, 4));
		map_TestChamber.col_CollisionData[8].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(38, 19), sf::Vector2f(-1, 5));

		// Right Collisions -- BLUE
		map_TestChamber.col_CollisionData[9].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(36, 19), sf::Vector2f(1, 5));
		map_TestChamber.col_CollisionData[10].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(46, 0), sf::Vector2f(1, 24));
		map_TestChamber.col_CollisionData[11].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(42, 18), sf::Vector2f(1, 1));
		map_TestChamber.col_CollisionData[12].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(42, 13), sf::Vector2f(1, 1));


		// Ceiling Collisions -- YELLOW
		map_TestChamber.col_CollisionData[13].InitializeCollision(PT_CEILING, true, sf::Vector2f(42, 19), sf::Vector2f(4, -1));
		map_TestChamber.col_CollisionData[14].InitializeCollision(PT_CEILING, true, sf::Vector2f(42, 14), sf::Vector2f(4, -1));
		map_TestChamber.col_CollisionData[15].InitializeCollision(PT_CEILING, true, sf::Vector2f(4, 4), sf::Vector2f(42, -1));

		
		// Platform Collisions
		map_TestChamber.pla_PlatformData[0].InitializePlatform(sf::Vector2f(34, 21), sf::Vector2f(2, .25));
		map_TestChamber.pla_PlatformData[1].InitializePlatform(sf::Vector2f(38, 21), sf::Vector2f(2, .25));
		map_TestChamber.pla_PlatformData[2].InitializePlatform(sf::Vector2f(34, 15), sf::Vector2f(6, .25));
		map_TestChamber.pla_PlatformData[3].InitializePlatform(sf::Vector2f(38, 10), sf::Vector2f(3, .25));
		map_TestChamber.pla_PlatformData[4].InitializePlatform(sf::Vector2f(6, 7), sf::Vector2f(31, .25));
		for (int count = 0; count < map_Selected.int_NumPlat; count++)
		{
			int index = 16 + (count * 4);
			map_TestChamber.CreatePlatform(index, map_TestChamber.pla_PlatformData[count]);
		}

		

		// Slope Collisions
		map_TestChamber.slo_SlopeData[0].InitializeSlope(RIGHT, false, sf::Vector2f(23, 19), sf::Vector2f(2, 1));
		map_TestChamber.slo_SlopeData[1].InitializeSlope(LEFT, false, sf::Vector2f(28, 19), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[2].InitializeSlope(LEFT, false, sf::Vector2f(29, 20), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[3].InitializeSlope(LEFT, false, sf::Vector2f(30, 21), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[4].InitializeSlope(LEFT, false, sf::Vector2f(31, 22), sf::Vector2f(1, 1));
		map_TestChamber.slo_SlopeData[5].InitializeSlope(LEFT, false, sf::Vector2f(32, 23), sf::Vector2f(1, 1));
	}


	//Arena 1
	{
		// Prep Textures
		if (!map_Arena1.txu_BackgroundImage.loadFromFile("Sprites/Backgrounds/Skyline.jpg"))
		{
			std::cout << "Background Image Failed to load" << std::endl;
		}
		if (!map_Arena1.txu_LevelImage.loadFromFile("Sprites/Backgrounds/Arena 1.png"))
		{
			std::cout << "Level Image Failed to load" << std::endl;
		}

		map_Arena1.int_NumColl = 29;
		map_Arena1.int_NumPlat = 6;
		map_Arena1.int_NumSlop = 1;
		map_Arena1.int_NumEnemies = 0;

		map_Arena1.col_CollisionData.resize(MAXCOLLISIONS);
		map_Arena1.slo_SlopeData.resize(MAXSLOPES);
		map_Arena1.pla_PlatformData.resize(MAXPLATFORMS);
		map_Arena1.et_EnemyData.resize(MAXENEMIES);
		map_Arena1.vec_EnemySpawn.resize(MAXENEMIES);


		// Spawn Location
		map_Arena1.vec_PlayerSpawn.x = X_64(5.5);
		map_Arena1.vec_PlayerSpawn.y = X_64(18.5);

		// Collisions
		map_Arena1.col_CollisionData[0].InitializeCollision(PT_FLOOR, true, sf::Vector2f(4, 20), sf::Vector2f(42, 1));
		map_Arena1.col_CollisionData[1].InitializeCollision(PT_FLOOR, true, sf::Vector2f(41, 16), sf::Vector2f(5, 1));
		map_Arena1.col_CollisionData[2].InitializeCollision(PT_CEILING, true, sf::Vector2f(4, 4), sf::Vector2f(42, -1));
		map_Arena1.col_CollisionData[3].InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(4, 4), sf::Vector2f(-1, 16));
		map_Arena1.col_CollisionData[4].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(46, 4), sf::Vector2f(1, 16));
		map_Arena1.col_CollisionData[5].InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(41, 16), sf::Vector2f(1, 5));

		//map_Arena1.slo_SlopeData[0].InitializeSlope(RIGHT, false, sf::Vector2f(33, 15), sf::Vector2f(8, 5));
	}
}