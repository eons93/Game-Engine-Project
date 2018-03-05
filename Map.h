#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionObject.h"
#include "Constants.h"
#include "Enumerations.h"
#include "Enemy.h"


class EnemyObject;

using namespace sf;

class Map
{
private:
	
	
public:
	Map();

	// Maps Physical Information
	std::vector<CollisionObject> CollisionData;
	std::vector<SlopeObject> SlopeData;
	std::vector<PlatformObject> PlatformData;



	//CollisionObject CollisionData[MAXCOLLISIONS];
	//SlopeObject SlopeData[MAXSLOPES];
	//PlatformObject PlatformData[MAXPLATFORMS];



	// Maps Textures
	sf::Texture bgImage;
	sf::Texture levelImage;

	// Spawn Points
	sf::Vector2f playerSpawn;
	

};

