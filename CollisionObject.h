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
	sf::RectangleShape rs_CollisionArea;	
	bool bol_Barrier;
	PlatformType pt_Type;					

};

class SlopeObject
{
private:

public:
	SlopeObject();
	void InitializeSlope(bool direction, bool invert, sf::Vector2f position, sf::Vector2f size);

	CollisionObject col_TopCollision;
	CollisionObject col_BottomCollision;
	CollisionObject col_LeftCollision;
	CollisionObject col_RightCollision;

	float flo_Slope;

	bool bol_LeftorRight;
	bool bol_Inverted;
};

class PlatformObject
{
private:

public:
	PlatformObject();
	void InitializePlatform(sf::Vector2f position, sf::Vector2f size);

	sf::RectangleShape rs_Platform;

	CollisionObject col_TopCollision;
	CollisionObject col_BottomCollision;
	CollisionObject col_LeftCollision;
	CollisionObject col_RightCollision;
};

