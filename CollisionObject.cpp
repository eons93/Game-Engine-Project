#include "stdafx.h"
#include "CollisionObject.h"
#include "Constants.h"
#include <iostream>
#include "GeneralFunctions.h"


CollisionObject::CollisionObject()
{
	// Default Values
	rs_CollisionArea.setOutlineThickness(-1);
	rs_CollisionArea.setOutlineColor(sf::Color(0, 0, 255));
	rs_CollisionArea.setFillColor(sf::Color(0, 0, 0, 0));
	rs_CollisionArea.setPosition(sf::Vector2f(-100, -100));
	pt_Type = PT_FLOOR;
	
	txt_Identifier.setCharacterSize(FONTSIZECOLLISION);

	sf::Font font;
	if (!font.loadFromFile("The Citadels.otf"))
	{
		std::cout << "font failed to load" << std::endl;
	}

	txt_Identifier.setFont(font);
}

// Streamline Collision creation
void CollisionObject::InitializeCollision(PlatformType platformT, bool stopper, sf::Vector2f position, sf::Vector2f size)
{
	// Place input values into respective collision data slots
	pt_Type = platformT;
	bol_Barrier = stopper;

	// Placeholders while inputted values are altered
	sf::Vector2f colPosition;
	sf::Vector2f colSize;
	sf::Vector2f textPosition;

	// ALter coordinates based on collision type

	if (stopper == true)
	{
		switch (platformT)
		{
		case PT_FLOOR:
			colPosition.x = BitConvert64(position.x) + 2;
			colPosition.y = BitConvert64(position.y);
			colSize.x = BitConvert64(size.x) - 4;
			colSize.y = BitConvert64(size.y);
			break;
		case PT_CEILING:
			colPosition.x = BitConvert64(position.x) + 2;
			colPosition.y = BitConvert64(position.y) + 1;
			colSize.x = BitConvert64(size.x) - 4;
			colSize.y = BitConvert64(size.y);
			break;
		case PT_LEFT_WALL:
			colPosition.x = BitConvert64(position.x);
			colPosition.y = BitConvert64(position.y) + 6;
			colSize.x = BitConvert64(size.x);
			colSize.y = BitConvert64(size.y) - 11;
			break;
		case PT_RIGHT_WALL:
			colPosition.x = BitConvert64(position.x);
			colPosition.y = BitConvert64(position.y) + 6;
			colSize.x = BitConvert64(size.x);
			colSize.y = BitConvert64(size.y) - 11;
			break;
		}
	}
	else
	{
		switch (platformT)
		{
		case PT_FLOOR:
			colPosition.x = BitConvert64(position.x) - 8;
			colPosition.y = BitConvert64(position.y) - 8;
			colSize.x = BitConvert64(size.x) + 16;
			colSize.y = BitConvert64(size.y);
			break;
		case PT_CEILING:
			colPosition.x = BitConvert64(position.x) - 8;
			colPosition.y = BitConvert64(position.y) + 8;
			colSize.x = BitConvert64(size.x) + 16;
			colSize.y = BitConvert64(size.y);
			break;
		case PT_LEFT_WALL:
			colPosition.x = BitConvert64(position.x) + 8;
			colPosition.y = BitConvert64(position.y) - 8;
			colSize.x = BitConvert64(size.x);
			colSize.y = BitConvert64(size.y) + 16;
			break;
		case PT_RIGHT_WALL:
			colPosition.x = BitConvert64(position.x) - 8;
			colPosition.y = BitConvert64(position.y) - 8;
			colSize.x = BitConvert64(size.x);
			colSize.y = BitConvert64(size.y) + 16;
			break;
		}
	}

	rs_CollisionArea.setPosition(colPosition);
	rs_CollisionArea.setSize(colSize);

	// Assign unique colors to each surface type
	switch (platformT)
	{
	case PT_FLOOR:
		//textPosition.x = colPosition.x + (colSize.x / 2);
		//textPosition.y = colPosition.y + FONTSIZECOLLISION;
		textPosition = colPosition;

		rs_CollisionArea.setOutlineColor(sf::Color(255, 0, 0));
		txt_Identifier.setFillColor(sf::Color(255, 0, 0));
		txt_Identifier.setPosition(textPosition);
		break;
	case PT_LEFT_WALL:
		//textPosition.x = colPosition.x;
		//textPosition.y = colPosition.y + (colSize.y / 2);
		textPosition = colPosition;

		rs_CollisionArea.setOutlineColor(sf::Color(0, 255, 0));
		txt_Identifier.setFillColor(sf::Color(0, 255, 0));
		break;
	case PT_RIGHT_WALL:
		//textPosition.x = colPosition.x;
		//textPosition.y = colPosition.y + FONTSIZECOLLISION;
		textPosition = colPosition;

		rs_CollisionArea.setOutlineColor(sf::Color(0, 0, 255));
		txt_Identifier.setFillColor(sf::Color(0, 0, 255));
		break;
	case PT_CEILING:

		textPosition = colPosition;
		rs_CollisionArea.setOutlineColor(sf::Color(255, 255, 0));
		txt_Identifier.setFillColor(sf::Color(255, 255, 0));
		break;
	}
}


SlopeObject::SlopeObject()
{
	
	col_TopCollision.InitializeCollision(PT_FLOOR, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	col_BottomCollision.InitializeCollision(PT_CEILING, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	col_LeftCollision.InitializeCollision(PT_RIGHT_WALL, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	col_RightCollision.InitializeCollision(PT_LEFT_WALL, false, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	bol_Inverted = false;
	bol_LeftorRight = LEFT;
	flo_Slope = 1;
}

void SlopeObject::InitializeSlope(bool direction, bool invert, sf::Vector2f position, sf::Vector2f size)
{
	// Place input values into respective collision data slots
	bol_LeftorRight = direction;
	bol_Inverted = invert;
	flo_Slope = size.x / size.y;

	// Variables to increase readability
	float top = position.y;
	float left = position.x;
	float height = size.y;
	float width = size.x;

	col_TopCollision.InitializeCollision(PT_FLOOR, false, sf::Vector2f(left, top), sf::Vector2f(width, 0));
	col_BottomCollision.InitializeCollision(PT_CEILING, false, sf::Vector2f(left, top + height), sf::Vector2f(width, 0));
	col_LeftCollision.InitializeCollision(PT_LEFT_WALL, false, sf::Vector2f(left + width, top), sf::Vector2f(0, height));
	col_RightCollision.InitializeCollision(PT_RIGHT_WALL, false, sf::Vector2f(left, top), sf::Vector2f(0, height));
	
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

	transPosition.x = BitConvert64(position.x);
	transPosition.y = BitConvert64(position.y);
	transSize.x = BitConvert64(size.x);
	transSize.y = BitConvert64(size.y);

	rs_Platform.setPosition(transPosition);
	rs_Platform.setSize(transSize);
	rs_Platform.setFillColor(sf::Color(5, 5, 5));

	col_TopCollision.InitializeCollision(PT_FLOOR, true, sf::Vector2f(left, top), sf::Vector2f(width, 0));
	col_BottomCollision.InitializeCollision(PT_CEILING, true, sf::Vector2f(left, top + height), sf::Vector2f(width, 0));
	col_LeftCollision.InitializeCollision(PT_LEFT_WALL, true, sf::Vector2f(left + width, top), sf::Vector2f(0, height));
	col_RightCollision.InitializeCollision(PT_RIGHT_WALL, true, sf::Vector2f(left, top), sf::Vector2f(0, height));
}