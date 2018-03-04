#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"


void Level::loadEnemies()
{
	loadAnimations();

	// Grunt Enemy
	{
		grunt.name = "GRUNT";
		
		grunt.idle = grunt_idle;
		grunt.fall = grunt_fall;
		
		//grunt.Update();
		//grunt.currentState_Animation = grunt.currentAnimationFunc();
		
	}
}