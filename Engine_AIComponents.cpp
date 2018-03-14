#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"
#include "Engine.h"


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
			enemy.sta_Current.Facing = LEFT;
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
			enemy.sta_Current.Facing = RIGHT;
		}
		break;
	}
}