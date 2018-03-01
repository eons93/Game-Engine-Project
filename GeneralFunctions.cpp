#include "stdafx.h"
#include "GeneralFunctions.h"
#include <string>
#include <sstream>

using namespace std;

// Converts values into strings for displaying purposes
std::string stringConvert(int value)
{
	string String = static_cast<ostringstream*>(&(ostringstream() << value))->str();
	return String;
}

float bitConvert64(float input)
{
	float converted = input * 64;
	return converted;
}