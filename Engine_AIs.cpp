#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"
#include "Engine.h"


void Engine::EliteAI(float ElapsedTime, EnemyObject &enemy)
{
	// Assign AI State
	if (enemy.CheckLowHealth() == true)
	{
		enemy.ais_CurrentState = FLEE;
	}
	else if (enemy.CheckLOS() == true)
	{
		if (enemy.CheckRange() == true)
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
		point1.x = BitConvert64(20);
		point1.y = BitConvert64(19);
		sf::Vector2f point2;
		point2.x = BitConvert64(5);
		point2.y = BitConvert64(19);

		//Patrol(ElapsedTime, enemy, point1, point2);
		break;
	}
}


void Engine::GruntAI(float ElapsedTime, EnemyObject &enemy)
{
	// Assign AI State
	if (enemy.CheckLowHealth() == true)
	{
		enemy.ais_CurrentState = FLEE;
	}
	else if (enemy.CheckLOS() == true)
	{
		if (enemy.CheckRange() == true)
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
		point1.x = BitConvert64(20);
		point1.y = BitConvert64(19);
		sf::Vector2f point2;
		point2.x = BitConvert64(5);
		point2.y = BitConvert64(19);

		//Patrol(ElapsedTime, enemy, point1, point2);
		break;
	}
}