#pragma once
#include "Enumerations.h"
#include <SFML/Graphics.hpp>


using namespace sf;

class CollisionObject
{
private:

public:
	CollisionObject();
	void InitializeCollision(PlatformType platformT, bool stopper, sf::Vector2f position, sf::Vector2f size);

	//collision data
	sf::RectangleShape collisionArea;	// Physical Representation
	bool barrier;
	PlatformType type;					// Which surface
	bool show;							// Toggle visability for developer mode
	bool orientation;					// Horizontal or Verticle

};

class SlopeObject
{
private:

public:
	SlopeObject();
	void InitializeSlope(bool direction, bool invert, sf::Vector2f position, sf::Vector2f size);

	CollisionObject topCollision;
	CollisionObject bottomCollision;
	CollisionObject leftCollision;
	CollisionObject rightCollision;

	float slope;

	bool left_right;
	bool inverted;
};

class PlatformObject
{
private:

public:
	PlatformObject();
	void InitializePlatform(sf::Vector2f position, sf::Vector2f size);

	sf::RectangleShape platform;

	CollisionObject topCollision;
	CollisionObject bottomCollision;
	CollisionObject leftCollision;
	CollisionObject rightCollision;
};

