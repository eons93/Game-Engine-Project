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
	ene_Elite.str_Name = "ELITE";
	ene_Elite.int_ID = 2;
	ene_Elite.ani_Idle = ani_EliteIdle;
	ene_Elite.ani_Fall = ani_EliteFall;
	ene_Elite.ani_Run = ani_EliteRun;

	ene_Elite.att_Stats.MovementSpeed = 128;
	ene_Elite.att_Stats.Health = 100;
	ene_Elite.att_Stats.Armor = 50;
	ene_Elite.att_Stats.Shield = 100;

	ene_Grunt.str_Name = "GRUNT";
	ene_Grunt.int_ID = 1;
	ene_Grunt.ani_Idle = ani_GruntIdle;
	ene_Grunt.ani_Fall = ani_GruntFall;
	ene_Grunt.ani_Run = ani_GruntRun;

	ene_Grunt.att_Stats.MovementSpeed = 128;
	ene_Grunt.att_Stats.Health = 50;
	ene_Grunt.att_Stats.Armor = 0;
	ene_Grunt.att_Stats.Shield = 0;

}
