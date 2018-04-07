#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionObject.h"
#include "Constants.h"
#include "Enumerations.h"
#include "Enemy.h"


//class EnemyObject;

using namespace sf;

class Map
{
private:
	
	
public:
	Map();

	void CreatePlatform(int indexStart, PlatformObject platform);

	// Maps Physical Information
	std::vector<CollisionObject> col_CollisionData;
	std::vector<SlopeObject> slo_SlopeData;
	std::vector<PlatformObject> pla_PlatformData;
	std::vector<EnemyType> et_EnemyData;
	
	// Cycle Limiters
	int int_NumEnemies;
	int int_NumColl;
	int int_NumPlat;
	int int_NumSlop;
	std::vector<int> int_LoadedCollision;
	int int_MaxCollisionIndex;
	std::vector<int> int_LoadedEnemies;
	int int_MaxEnemyIndex;


	// Maps Textures
	sf::Texture txu_BackgroundImage;
	sf::Texture txu_LevelImage;

	// Spawn Points
	sf::Vector2f vec_PlayerSpawn;
	std::vector<sf::Vector2f> vec_EnemySpawn;

};

