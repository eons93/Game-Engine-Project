#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"



using namespace sf;

class Level
{
private:


public:
	Level();

	// Loads Level selected
	void attachTexture();
	void attachMap(Map map);

	// Update Functions
	void detectCollision1(Player &Lplayer);
	
	// Holds selected map's Entities
	sf::RectangleShape background;
	sf::Sprite levelStructure;

	// Preps maps to be used
	void loadMaps();
	Map selectedMap;

	// Maps to choose from
	Map playground;

};