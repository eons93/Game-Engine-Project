#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionObject.h"
#include "Constants.h"
#include "Enumerations.h"


using namespace sf;

class Map
{
private:
	
	
public:
	Map();

	// Maps Physical Information
	CollisionObject CollisionData[MAXCOLLISIONS];
	SlopeObject SlopeData[MAXSLOPES];
	PlatformObject PlatformData[MAXPLATFORMS];

	// Maps Textures
	sf::Texture bgImage;
	sf::Texture levelImage;

	// Spawn Points
	sf::Vector2f playerSpawn;

};

