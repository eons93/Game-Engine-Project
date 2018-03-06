#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"
#include "Engine.h"

void Engine::LoadEnemies()
{
	ene_Grunt.str_Name = "GRUNT";
	ene_Grunt.ani_Idle = ani_GruntIdle;
	ene_Grunt.ani_Fall = ani_GruntFall;

}
