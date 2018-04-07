#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"
#include "Engine.h"
#include "Structs.h"


void Engine::Patrol(float ElapsedTime, EnemyObject &enemy, sf::Vector2f point1, sf::Vector2f point2)
{
	float leftPoint;
	float rightPoint;
	float destination;

	if (point1.x < point2.x)
	{
		leftPoint = point1.x;
		rightPoint = point2.x;
	}
	else
	{
		leftPoint = point2.x;
		rightPoint = point1.x;
	}

	switch (enemy.GetState().Facing)
	{
	case RIGHT:
		destination = rightPoint;
		if (enemy.GetPosition().x < destination)
		{
			enemy.MoveRight(ElapsedTime);
		}
		else
		{
			enemy.flo_VisionAngle -= 180;
		}
		break;
	case LEFT:
		destination = leftPoint;
		if (enemy.GetPosition().x > destination)
		{
			enemy.MoveLeft(ElapsedTime);
		}
		else
		{
			enemy.flo_VisionAngle += 180;
		}
		break;
	}
}

void Engine::Flee(float ElapsedTime, EnemyObject &enemy, float playerAngle)
{
	if (playerAngle > 0 && playerAngle < 180)
	{
		enemy.MoveRight(ElapsedTime);
	}
	else
	{
		enemy.MoveLeft(ElapsedTime);
	}
}

void Engine::Chase(float ElapsedTime, EnemyObject &enemy, float playerAngle)
{
	if (playerAngle > 0 && playerAngle < 180)
	{
		enemy.MoveLeft(ElapsedTime);
	}
	else
	{
		enemy.MoveRight(ElapsedTime);
	}
}

void Engine::AttackPlayer(float ElapsedTime, EnemyObject &enemy, Attack attack, Player &player)
{
	if (enemy.sta_Current.Shooting == false && enemy.sta_Current.Meleeing == false)
	{
		enemy.EngageAttack(attack, player);
	}
	enemy.ProcessAttack(ElapsedTime, attack);
}

bool Engine::CheckWalls(EnemyObject enemy, Player player)
{
	// This function tests the intersection of the line between enemy and player against the line of a 
	// collisions trueA vector and trueB vector. This function should return true if no single barrier
	// hinders sight of the enemy.

	bool output = true;

	LinearFunc Enemy_Player = LinearOf(enemy.GetPosition(), player.GetPosition());
	
	for (int count = 0; count < map_Selected.int_NumColl; count++)
	{
		if (DetectObstruction(enemy, player, Enemy_Player, map_Selected.col_CollisionData[count]) == true)
		{
			return false;
		}
	}
	return output;
}

bool Engine::DetectObstruction(EnemyObject enemy, Player player, LinearFunc enemy_Player, CollisionObject barrier)
{
	// This function tests a single collision object against the positions of a player and enemy to detect if it is in the way. 
	// This function will return false if there was no obstruction.

	bool output;

	LinearFunc CollisionPoints = LinearOf(barrier.vec_TrueA,
		barrier .vec_TrueB);
	
	sf::Vector2f intersect = IntersectOf(enemy_Player, CollisionPoints);

	if (intersect.x >= 0 && intersect.y >= 0)
	{
		if (intersect.x >= barrier.vec_TrueA.x && intersect.x <= barrier.vec_TrueB.x)
		{
			if (intersect.y >= barrier.vec_TrueA.y && intersect.y <= barrier.vec_TrueB.y)
			{
				float playerDistance = DistanceOf(enemy.GetPosition(), player.GetPosition());
				float intersectDis = DistanceOf(enemy.GetPosition(), intersect);

				if (intersectDis < playerDistance)
				{
					output = true;
				}
				else
				{
					output = false;
				}
			}
			else
			{
				output = false;
			}
		}
		else
		{
			output = false;
		}
	}
	else
	{
		output = false;
	}
	return output;
}