#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"
#include "Engine.h"


void Engine::EliteAI(float ElapsedTime, EnemyObject &enemy, Player &player)
{
	float playerDistance = DistanceOf(enemy.GetPosition(), player.GetPosition());
	float playerAngle = AngleOf(enemy.GetPosition(), player.GetPosition());

	//Print("Vision Angle: " + StringConvert(enemy.flo_VisionAngle));
	//Print("Player Angle: " + StringConvert(playerAngle));
	//Print("Player Distance: " + StringConvert(playerDistance));


	// Assign AI State
	if (player.sta_Current.CurrentState == CS_DEAD)
	{
		enemy.ais_CurrentState = PATROL;
	}
	else
	{
		if (enemy.CheckLowHealth() == true)
		{
			enemy.ais_CurrentState = FLEE;
		}
		else if (enemy.CheckLOS(playerAngle, playerDistance) == true)
		{
			if (CheckWalls(enemy, player) == true)
			{
				if (enemy.CheckRange(playerDistance) == true)
				{
					enemy.ais_CurrentState = ATTACK;
				}
				else
				{
					enemy.ais_CurrentState = CHASE;
				}
			}
		}
		else
		{
			enemy.ais_CurrentState = PATROL;
		}
	}

	// Execute Enemy Action
	switch (enemy.ais_CurrentState)
	{
	case FLEE:
		Flee(ElapsedTime, enemy, playerAngle);
		//std::cout << "Flee" << std::endl;
		break;
	case ATTACK:
		AttackPlayer(ElapsedTime, enemy, enemy.att_Stats.Attack[0], player);
		//std::cout << "Attack" << std::endl;
		break;
	case CHASE:
		Chase(ElapsedTime, enemy, playerAngle);
		//std::cout << "Chase" << std::endl;
		break;
	case PATROL:
		//std::cout << "Patrol" << std::endl;
		
		sf::Vector2f point1;
		point1.x = X_64(20);
		point1.y = X_64(19);
		sf::Vector2f point2;
		point2.x = X_64(5);
		point2.y = X_64(19);

		Patrol(ElapsedTime, enemy, point1, point2);
		break;
	}
}


void Engine::GruntAI(float ElapsedTime, EnemyObject &enemy, Player player)
{
	// Assign AI State
	if (enemy.CheckLowHealth() == true)
	{
		enemy.ais_CurrentState = FLEE;
	}
	else if (enemy.CheckLOS(0,0) == true)
	{
		if (enemy.CheckRange(0) == true)
		{
			enemy.ais_CurrentState = ATTACK;
		}
		else
		{
			enemy.ais_CurrentState = CHASE;
		}
	}
	else
	{
		enemy.ais_CurrentState = PATROL;
	}

	// Execute Enemy Action
	switch (enemy.ais_CurrentState)
	{
	case FLEE:
		std::cout << "ERROR: FLEEING" << std::endl;
		break;
	case ATTACK:
		std::cout << "ERROR: ATTACKING" << std::endl;
		break;
	case CHASE:
		std::cout << "ERROR: CHASEING" << std::endl;
		break;
	case PATROL:

		
		sf::Vector2f point1;
		point1.x = X_64(20);
		point1.y = X_64(19);
		sf::Vector2f point2;
		point2.x = X_64(5);
		point2.y = X_64(19);

		//Patrol(ElapsedTime, enemy, point1, point2);
		break;
	}
}