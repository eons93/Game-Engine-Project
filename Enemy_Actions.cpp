#include "stdafx.h"
#include "Enemy.h"
#include "Enumerations.h"
#include <iostream>

void EnemyObject::MoveLeft(float ElapsedTime)
{
	sta_Current.MovingR = false;
	sta_Current.MovingL = true;
	vec_Velocity.x -= att_Stats.MovementSpeed * ElapsedTime;
}

void EnemyObject::MoveRight(float ElapsedTime)
{
	sta_Current.MovingR = true;
	sta_Current.MovingL = false;
	vec_Velocity.x += att_Stats.MovementSpeed * ElapsedTime;
}