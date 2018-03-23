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


void EnemyObject::recieveDamage(float incomingDmg, DamageReport &report)
{
	float postShieldDmg = incomingDmg - GetCurrentShields();
	report.ShieldDmg = GetCurrentShields() - postShieldDmg;
	flo_CurrentShields -= incomingDmg;

	if (GetCurrentShields() < 0)
	{
		flo_CurrentShields = 0;
	}
	if (postShieldDmg < 0)
	{
		postShieldDmg = 0;
	}

	// Calculate Damage Reduction from Armor Value
	float reduct = (-att_Stats.Armor / (att_Stats.Armor + 100)) + 1;
	float postArmorDmg = postShieldDmg * reduct;
	report.HealthDmg = postArmorDmg;
	flo_CurrentHealth -= postArmorDmg;
	sta_Current.TookDamage = true;
}