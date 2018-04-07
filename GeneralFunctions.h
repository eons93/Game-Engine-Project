#pragma once
#include <string>
#include "Enemy.h"

std::string StringConvert(float value);
void Print(std::string string);

float X_64(float input);

float getRandomNumber(float min, float max);

sf::Color HealthPercentColor(float health);
sf::Color ShieldPercentColor(float shields);
float ArmorReduction(float armor);

LinearFunc LinearOf(sf::Vector2f A, sf::Vector2f B);
sf::Vector2f IntersectOf(LinearFunc A, LinearFunc B);
ParabolicFunc ParabolaOf(float width, float height);

float SlopeOf(sf::Vector2f Origin, sf::Vector2f Destination);
float AngleOf(sf::Vector2f Origin, sf::Vector2f Destination);
float SlopeToAngle(float input);
float AngleToSlope(float input);
float DistanceOf(sf::Vector2f Origin, sf::Vector2f Destination);