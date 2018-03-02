#include "stdafx.h"
#include "CollisionObject.h"
#include "Constants.h"
#include <iostream>
#include "GeneralFunctions.h"


CollisionObject::CollisionObject()
{
	// Default Values
	collisionArea.setOutlineThickness(-1);
	collisionArea.setOutlineColor(sf::Color(0, 0, 255));
	collisionArea.setFillColor(sf::Color(0, 0, 0, 0));
	collisionArea.setPosition(sf::Vector2f(-100, -100));
	orientation = HORIZONTAL;
	type = FLOOR;
	
	identifier.setCharacterSize(FONTSIZECOLLISION);

	sf::Font font;
	if (!font.loadFromFile("The Citadels.otf"))
	{
		std::cout << "font failed to load" << std::endl;
	}

	identifier.setFont(font);
}

// Streamline Collision creation
void CollisionObject::InitializeCollision(PlatformType platformT, bool stopper, sf::Vector2f position, sf::Vector2f size)
{
	// Place input values into respective collision data slots
	type = platformT;
	barrier = stopper;

	// Placeholders while inputted values are altered
	sf::Vector2f colPosition;
	sf::Vector2f colSize;
	sf::Vector2f textPosition;

	// ALter coordinates based on collision type

	if (stopper == true)
	{
		switch (platformT)
		{
		case FLOOR:
			colPosition.x = bitConvert64(position.x) + 2;
			colPosition.y = bitConvert64(position.y);
			colSize.x = bitConvert64(size.x) - 4;
			colSize.y = bitConvert64(size.y);
			break;
		case CEILING:
			colPosition.x = bitConvert64(position.x) + 2;
			colPosition.y = bitConvert64(position.y) + 1;
			colSize.x = bitConvert64(size.x) - 4;
			colSize.y = bitConvert64(size.y);
			break;
		case LEFT_WALL:
			colPosition.x = bitConvert64(position.x);
			colPosition.y = bitConvert64(position.y) + 6;
			colSize.x = bitConvert64(size.x);
			colSize.y = bitConvert64(size.y) - 11;
			break;
		case RIGHT_WALL:
			colPosition.x = bitConvert64(position.x);
			colPosition.y = bitConvert64(position.y) + 6;
			colSize.x = bitConvert64(size.x);
			colSize.y = bitConvert64(size.y) - 11;
			break;
		}
	}
	else
	{
		switch (platformT)
		{
		case FLOOR:
			colPosition.x = bitConvert64(position.x) - 8;
			colPosition.y = bitConvert64(position.y) - 8;
			colSize.x = bitConvert64(size.x) + 16;
			colSize.y = bitConvert64(size.y);
			break;
		case CEILING:
			colPosition.x = bitConvert64(position.x) - 8;
			colPosition.y = bitConvert64(position.y) + 8;
			colSize.x = bitConvert64(size.x) + 16;
			colSize.y = bitConvert64(size.y);
			break;
		case LEFT_WALL:
			colPosition.x = bitConvert64(position.x) + 8;
			colPosition.y = bitConvert64(position.y) - 8;
			colSize.x = bitConvert64(size.x);
			colSize.y = bitConvert64(size.y) + 16;
			break;
		case RIGHT_WALL:
			colPosition.x = bitConvert64(position.x) - 8;
			colPosition.y = bitConvert64(position.y) - 8;
			colSize.x = bitConvert64(size.x);
			colSize.y = bitConvert64(size.y) + 16;
			break;
		}
	}

	collisionArea.setPosition(colPosition);
	collisionArea.setSize(colSize);

	// Assign unique colors to each surface type
	switch (platformT)
	{
	case FLOOR:
		//textPosition.x = colPosition.x + (colSize.x / 2);
		//textPosition.y = colPosition.y + FONTSIZECOLLISION;
		textPosition = colPosition;

		collisionArea.setOutlineColor(sf::Color(255, 0, 0));
		identifier.setFillColor(sf::Color(255, 0, 0));
		identifier.setPosition(textPosition);
		break;
	case LEFT_WALL:
		//textPosition.x = colPosition.x;
		//textPosition.y = colPosition.y + (colSize.y / 2);
		textPosition = colPosition;

		collisionArea.setOutlineColor(sf::Color(0, 255, 0));
		identifier.setFillColor(sf::Color(0, 255, 0));
		break;
	case RIGHT_WALL:
		//textPosition.x = colPosition.x;
		//textPosition.y = colPosition.y + FONTSIZECOLLISION;
		textPosition = colPosition;

		collisionArea.setOutlineColor(sf::Color(0, 0, 255));
		identifier.setFillColor(sf::Color(0, 0, 255));
		break;
	case CEILING:

		textPosition = colPosition;
		collisionArea.setOutlineColor(sf::Color(255, 255, 0));
		identifier.setFillColor(sf::Color(255, 255, 0));
		break;
	}
}


SlopeObject::SlopeObject()
{
	
	topCollision.InitializeCollision(FLOOR, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	bottomCollision.InitializeCollision(CEILING, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	leftCollision.InitializeCollision(RIGHT_WALL, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	rightCollision.InitializeCollision(LEFT_WALL, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	inverted = false;
	left_right = LEFT;
	slope = 1;
}

void SlopeObject::InitializeSlope(bool direction, bool invert, sf::Vector2f position, sf::Vector2f size)
{
	// Place input values into respective collision data slots
	left_right = direction;
	inverted = invert;
	slope = size.x / size.y;

	// Variables to increase readability
	float top = position.y;
	float left = position.x;
	float height = size.y;
	float width = size.x;

	topCollision.InitializeCollision(FLOOR, false, sf::Vector2f(left, top), sf::Vector2f(width, 0));
	bottomCollision.InitializeCollision(CEILING, false, sf::Vector2f(left, top + height), sf::Vector2f(width, 0));
	leftCollision.InitializeCollision(LEFT_WALL, false, sf::Vector2f(left + width, top), sf::Vector2f(0, height));
	rightCollision.InitializeCollision(RIGHT_WALL, false, sf::Vector2f(left, top), sf::Vector2f(0, height));
	
}

PlatformObject::PlatformObject()
{

}

void PlatformObject::InitializePlatform(sf::Vector2f position, sf::Vector2f size)
{

	// Variables to increase readability
	float top = position.y;
	float left = position.x;
	float height = size.y;
	float width = size.x;

	sf::Vector2f transPosition;
	sf::Vector2f transSize;

	transPosition.x = bitConvert64(position.x);
	transPosition.y = bitConvert64(position.y);
	transSize.x = bitConvert64(size.x);
	transSize.y = bitConvert64(size.y);

	platform.setPosition(transPosition);
	platform.setSize(transSize);
	platform.setFillColor(sf::Color(5, 5, 5));

	topCollision.InitializeCollision(FLOOR, true, sf::Vector2f(left, top), sf::Vector2f(width, 0));
	bottomCollision.InitializeCollision(CEILING, true, sf::Vector2f(left, top + height), sf::Vector2f(width, 0));
	leftCollision.InitializeCollision(LEFT_WALL, true, sf::Vector2f(left + width, top), sf::Vector2f(0, height));
	rightCollision.InitializeCollision(RIGHT_WALL, true, sf::Vector2f(left, top), sf::Vector2f(0, height));
}