#pragma once
#include <SFML\Graphics.hpp>
#include "CollisionObject.h"
#include "Animation.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H


const int FONTSIZECOLLISION(8);

const bool MELEE(true);
const bool RANGE(false);

const bool RIGHT(true);
const bool LEFT(false);

const bool VERTICAL(true);
const bool HORIZONTAL(false);

const bool OUTPUT(true);
const bool INPUT(false);

//const float UNDEFINED(1 / 0);
//const float UNDEFINEDNEG(-(1 / 0));
const double PI(3.1415926);
const float GRAVITY(24.0);

const int MAXSLOPES(100);
const int MAXCOLLISIONS(200);
const int MAXPLATFORMS(100);
const int MAXENEMIES(100);




#endif

