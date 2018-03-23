#include "stdafx.h"
#include "GeneralFunctions.h"
#include "Player.h"
#include <string>
#include <sstream>

using namespace std;

// Converts values into strings for displaying purposes
std::string StringConvert(float value)
{
	string String = static_cast<ostringstream*>(&(ostringstream() << value))->str();
	return String;
}

float BitConvert64(float input)
{
	float converted = input * 64;
	return converted;
}

void EnemyDamage(EnemyObject &enemy, float damage)
{
	enemy.flo_CurrentHealth -= damage;
	enemy.sta_Current.TookDamage = true;
}

float getRandomNumber(float min, float max)
{
	// static used for efficiency, so we only calculate this value once
	static const double fraction = 1.0 / (RAND_MAX + 1.0);  
		
	// evenly distribute the random number across our range
	return (min + static_cast<float>((max - min + 1) * (rand() * fraction))) / 2;
}