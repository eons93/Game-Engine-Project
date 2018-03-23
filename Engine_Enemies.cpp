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
	ene_Elite.ani_Run = ani_EliteRun;

	ene_Elite.att_Stats.MovementSpeed = 128;
	ene_Elite.att_Stats.Health = 100;
	ene_Elite.att_Stats.Armor = 50;
	ene_Elite.att_Stats.Shield = 200;

	ene_Elite.att_Stats.MeleeAttack.type = MELEE;
	ene_Elite.att_Stats.MeleeAttack.Damage = 50;
	ene_Elite.att_Stats.MeleeAttack.AttackSpeed = 1;
	ene_Elite.att_Stats.MeleeAttack.CritChance = 0.1;
	ene_Elite.att_Stats.MeleeAttack.CritDamage = 2.0;
	ene_Elite.att_Stats.MeleeAttack.Range = BitConvert64(1.5);
	ene_Elite.att_Stats.MeleeAttack.AngleOffset = 0;
	ene_Elite.att_Stats.MeleeAttack.BottomOffset = 48;
	ene_Elite.att_Stats.MeleeAttack.TopOffset = 48;

	ene_Elite.att_Stats.RangeAttack.type = MELEE;
	ene_Elite.att_Stats.RangeAttack.Damage = 50;
	ene_Elite.att_Stats.RangeAttack.AttackSpeed = 1;
	ene_Elite.att_Stats.RangeAttack.CritChance = 0.1;
	ene_Elite.att_Stats.RangeAttack.CritDamage = 2.0;
	ene_Elite.att_Stats.RangeAttack.Range = BitConvert64(1.5);
	ene_Elite.att_Stats.RangeAttack.AngleOffset = 0;
	ene_Elite.att_Stats.RangeAttack.BottomOffset = 48;
	ene_Elite.att_Stats.RangeAttack.TopOffset = 48;

	// Grunt Enemy
	ene_Grunt.str_Name = "GRUNT";
	ene_Grunt.int_ID = 1;
	ene_Grunt.ani_Idle = ani_GruntIdle;
	ene_Grunt.ani_Death = ani_GruntDeath;
	ene_Grunt.ani_Fall = ani_GruntFall;
	ene_Grunt.ani_Run = ani_GruntRun;

	ene_Grunt.att_Stats.MovementSpeed = 128;
	ene_Grunt.att_Stats.Health = 50;
	ene_Grunt.att_Stats.Armor = 0;
	ene_Grunt.att_Stats.Shield = 30;

	ene_Grunt.att_Stats.MeleeAttack.type = MELEE;
	ene_Grunt.att_Stats.MeleeAttack.Damage = 50;
	ene_Grunt.att_Stats.MeleeAttack.AttackSpeed = 1;
	ene_Grunt.att_Stats.MeleeAttack.CritChance = 0.1;
	ene_Grunt.att_Stats.MeleeAttack.CritDamage = 2.0;
	ene_Grunt.att_Stats.MeleeAttack.Range = BitConvert64(1.5);
	ene_Grunt.att_Stats.MeleeAttack.AngleOffset = 0;
	ene_Grunt.att_Stats.MeleeAttack.BottomOffset = 48;
	ene_Grunt.att_Stats.MeleeAttack.TopOffset = 48;

	ene_Grunt.att_Stats.RangeAttack.type = MELEE;
	ene_Grunt.att_Stats.RangeAttack.Damage = 50;
	ene_Grunt.att_Stats.RangeAttack.AttackSpeed = 1;
	ene_Grunt.att_Stats.RangeAttack.CritChance = 0.1;
	ene_Grunt.att_Stats.RangeAttack.CritDamage = 2.0;
	ene_Grunt.att_Stats.RangeAttack.Range = BitConvert64(1.5);
	ene_Grunt.att_Stats.RangeAttack.AngleOffset = 0;
	ene_Grunt.att_Stats.RangeAttack.BottomOffset = 48;
	ene_Grunt.att_Stats.RangeAttack.TopOffset = 48;
}
