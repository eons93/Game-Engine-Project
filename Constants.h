#pragma once
#include <SFML\Graphics.hpp>
#include "CollisionObject.h"
#include "Animation.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H


const int FONTSIZECOLLISION(8);


const bool RIGHT(true);
const bool LEFT(false);

const bool VERTICAL(true);
const bool HORIZONTAL(false);

const float GRAVITY(1.0);

const int MAXSLOPES(20);
const int MAXCOLLISIONS(100);
const int MAXPLATFORMS(30);
const int MAXENEMIES(15);




#endif

