#include "stdafx.h"
#include "GeneralFunctions.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Converts values into strings for displaying purposes
std::string StringConvert(float value)
{
	string String = static_cast<ostringstream*>(&(ostringstream() << value))->str();
	return String;
}

void Print(std::string string)
{
	std::cout << string << std::endl;
}

float X_64(float input)
{
	float converted = input * 64;
	return converted;
}

float getRandomNumber(float min, float max)
{
	// static used for efficiency, so we only calculate this value once
	static const double fraction = 1.0 / (RAND_MAX + 1.0);  
		
	// evenly distribute the random number across our range
	return (min + static_cast<float>((max - min + 1) * (rand() * fraction))) / 2;
}

sf::Color HealthPercentColor(float health)
{
	sf::Color color(0, 255, 0);

	if (health > 50)
	{
		color.g = 255;
		color.r = (100 - health) * 5.10;
	}
	else
	{
		color.g = health * 5.10;
		color.r = 255;
	}

	return color;
}
sf::Color ShieldPercentColor(float shields)
{
	sf::Color color(0, 0, 255);
	
	color.g = shields * 2.55;

	return color;
}
float ArmorReduction(float armor)
{
	float output;
	
	if (armor < 0)
	{
		output = (-armor + 100) / 100;
	}
	else
	{
		output = (armor / (armor + 100));
	}

	return output;
}

LinearFunc LinearOf(sf::Vector2f pointA, sf::Vector2f pointB)
{
	LinearFunc output;

	if (pointA.x == pointB.x)
	{
		output.Slope = 10000;
		output.Intercept = ((output.Slope * pointA.x) - pointA.y) / -1;
	}
	else
	{
		output.Slope = SlopeOf(pointA, pointB);
		output.Intercept = ((output.Slope * pointA.x) - pointA.y) / -1;
	}

	if (output.Intercept == -0)
	{
		output.Intercept = 0;
	}

	return output;
}
sf::Vector2f IntersectOf(LinearFunc lineA, LinearFunc lineB)
{
	sf::Vector2f output;

	if (lineA.Slope == lineB.Slope)
	{
		output.x = -100;
		output.y = -100;
	}
	else
	{
		float leftSide = lineA.Slope - lineB.Slope;
		float rightSide = lineB.Intercept - lineA.Intercept;

		float holder = rightSide / leftSide;

		output.x = holder;

		output.y = (lineA.Slope * holder) + lineA.Intercept;
	}
	return output;
}
ParabolicFunc ParabolaOf(float width, float height)
{
	ParabolicFunc output;

	float scale = (width / 2) * (width / 2);

	output.Y_Scale = height / scale;
	output.X_Scale = (output.Y_Scale / 1) * width;
	output.Intercept = 0;

	std::cout << "y = " << output.Y_Scale << "x^2 + " << output.X_Scale << "x + " << output.Intercept << std::endl;

	return output;
}

float SlopeOf(sf::Vector2f Origin, sf::Vector2f Destination)
{
	float output;

	float dX = Destination.x - Origin.x;
	float dY = Destination.y - Origin.y;

	output = dY / dX;

	return output;
}
float AngleOf(sf::Vector2f Origin, sf::Vector2f Destination)
{
	float output;

	float dX = Destination.x - Origin.x;
	float dY = Destination.y - Origin.y;

	output = (atan2(dX, dY) * 180 / PI) + 180;

	return output;
}
float SlopeToAngle(float input)
{
	float output;

	float dX = 1;
	float dY = input;

	output = (atan(input) * 180 / PI) + 180;

	return output;
}
float AngleToSlope(float input)
{
	float output;

	output = tan((((input - 180) * PI) / 180));

	return output;
}
float DistanceOf(sf::Vector2f Origin, sf::Vector2f Destination)
{
	float output;

	float dX = Destination.x - Origin.x;
	float dY = Destination.y - Origin.y;

	if (dX < 0)
	{
		dX = dX * -1;
	}
	if (dY < 0)
	{
		dY = dY * -1;
	}

	float hypotenuse = (dX * dX) + (dY * dY);

	output = sqrt(hypotenuse);

	return output;
}