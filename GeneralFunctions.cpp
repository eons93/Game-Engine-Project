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