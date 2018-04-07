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
	// Elite Enemy
	ene_Elite.str_Name = "ELITE";
	ene_Elite.int_ID = 2;
	ene_Elite.ani_Idle = ani_EliteIdle;
	ene_Elite.ani_Death = ani_EliteDeath;
	ene_Elite.ani_Fall = ani_EliteFall;
	ene_Elite.ani_Jump = ani_EliteJump;
	ene_Elite.ani_Melee = ani_EliteMelee;
	ene_Elite.ani_AirMelee = ani_EliteMelee;
	ene_Elite.ani_Run = ani_EliteRun;
	ene_Elite.ani_Block = ani_EliteBlock;
	ene_Elite.ani_Duck = ani_EliteDuck;
	ene_Elite.ani_Roll = ani_EliteRoll;
	ene_Elite.txu_Firing = txu_EliteFiring;
	ene_Elite.txu_Aiming = txu_EliteAiming;
	ene_Elite.txu_NoShow = txu_EliteNoShow;

	ene_Elite.att_Stats.MovementSpeed = 128;
	ene_Elite.att_Stats.Health = 100;
	ene_Elite.att_Stats.Armor = 50;
	ene_Elite.att_Stats.Shield = 200;
	ene_Elite.att_Stats.Block = 0.5;
	ene_Elite.att_Stats.Dodge = 0.5;

	ene_Elite.att_Stats.Attack[0].type = RANGE;
	ene_Elite.att_Stats.Attack[0].Damage = 50;
	ene_Elite.att_Stats.Attack[0].AttackSpeed = 1;
	ene_Elite.att_Stats.Attack[0].CritChance = 0.1;
	ene_Elite.att_Stats.Attack[0].CritDamage = 2.0;
	ene_Elite.att_Stats.Attack[0].Range = X_64(5);
	ene_Elite.att_Stats.Attack[0].AngleOffset = 10;
	ene_Elite.att_Stats.Attack[0].BottomOffset = 0;
	ene_Elite.att_Stats.Attack[0].TopOffset = 0;

	ene_Elite.att_Stats.Attack[1].type = MELEE;
	ene_Elite.att_Stats.Attack[1].Damage = 50;
	ene_Elite.att_Stats.Attack[1].AttackSpeed = 1;
	ene_Elite.att_Stats.Attack[1].CritChance = 0.1;
	ene_Elite.att_Stats.Attack[1].CritDamage = 2.0;
	ene_Elite.att_Stats.Attack[1].Range = X_64(1.5);
	ene_Elite.att_Stats.Attack[1].AngleOffset = 0;
	ene_Elite.att_Stats.Attack[1].BottomOffset = 48;
	ene_Elite.att_Stats.Attack[1].TopOffset = 48;

	// Grunt Enemy
	ene_Grunt.str_Name = "GRUNT";
	ene_Grunt.int_ID = 1;
	ene_Grunt.ani_Idle = ani_GruntIdle;
	ene_Grunt.ani_Death = ani_GruntDeath;
	ene_Grunt.ani_Fall = ani_GruntFall;
	ene_Grunt.ani_Jump = ani_GruntJump;
	ene_Grunt.ani_Melee = ani_GruntMelee;
	ene_Grunt.ani_AirMelee = ani_GruntMelee;
	ene_Grunt.ani_Run = ani_GruntRun;
	ene_Grunt.ani_Block = ani_GruntBlock;
	ene_Grunt.ani_Duck = ani_GruntDuck;
	ene_Grunt.ani_Roll = ani_GruntRoll;
	ene_Grunt.txu_Firing = txu_GruntFiring;
	ene_Grunt.txu_Aiming = txu_GruntAiming;
	ene_Grunt.txu_NoShow = txu_GruntNoShow;

	ene_Grunt.att_Stats.MovementSpeed = 128;
	ene_Grunt.att_Stats.Health = 50;
	ene_Grunt.att_Stats.Armor = 0;
	ene_Grunt.att_Stats.Shield = 30;
	ene_Grunt.att_Stats.Block = 0.5;
	ene_Grunt.att_Stats.Dodge = 0.5;

	ene_Grunt.att_Stats.Attack[0].type = RANGE;
	ene_Grunt.att_Stats.Attack[0].Damage = 50;
	ene_Grunt.att_Stats.Attack[0].AttackSpeed = 1;
	ene_Grunt.att_Stats.Attack[0].CritChance = 0.1;
	ene_Grunt.att_Stats.Attack[0].CritDamage = 2.0;
	ene_Grunt.att_Stats.Attack[0].Range = X_64(5);
	ene_Grunt.att_Stats.Attack[0].AngleOffset = 10;
	ene_Grunt.att_Stats.Attack[0].BottomOffset = 0;
	ene_Grunt.att_Stats.Attack[0].TopOffset = 0;

	ene_Grunt.att_Stats.Attack[1].type = MELEE;
	ene_Grunt.att_Stats.Attack[1].Damage = 50;
	ene_Grunt.att_Stats.Attack[1].AttackSpeed = 1;
	ene_Grunt.att_Stats.Attack[1].CritChance = 0.1;
	ene_Grunt.att_Stats.Attack[1].CritDamage = 2.0;
	ene_Grunt.att_Stats.Attack[1].Range = X_64(1.5);
	ene_Grunt.att_Stats.Attack[1].AngleOffset = 0;
	ene_Grunt.att_Stats.Attack[1].BottomOffset = 48;
	ene_Grunt.att_Stats.Attack[1].TopOffset = 48;
}
