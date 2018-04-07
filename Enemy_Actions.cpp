#include "stdafx.h"
#include "Enemy.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Player.h"
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

// Jump Functions
void EnemyObject::EngageJump()
{
	sta_Current.Jumping = true;
	sta_Current.Falling = true;
	sta_Current.CanJump = false;
	vec_Velocity.y = 0;
}
void EnemyObject::ProcessJump(float ElapsedTime)
{
	// Jump Action Stats
	float jumpSpeed = 45;
	float jumpDuration = .5;
	static float jumpElapsed = 0;

	vec_Velocity.y -= jumpSpeed * ElapsedTime;

	jumpElapsed += ElapsedTime;
	if (jumpElapsed >= jumpDuration)
	{
		jumpElapsed = 0;
		DisengageJump();
	}
}
void EnemyObject::DisengageJump()
{
	sta_Current.Jumping = false;
}

// Duck Functions
void EnemyObject::EngageDuck()
{
	sta_Current.Ducking = true;
}
void EnemyObject::DisengageDuck()
{
	sta_Current.Ducking = false;
}

//------------------------------------COMBAT ACTIONS----------------------------------

// Roll Functions
void EnemyObject::EngageLeftRoll()
{
	sta_Current.Rolling = true;
	sta_Current.Facing = LEFT;
}
void EnemyObject::EngageRightRoll()
{
	sta_Current.Rolling = true;
	sta_Current.Facing = RIGHT;
}
void EnemyObject::ProcessRoll(float ElapsedTime)
{
	static bool bol_RollFaceHolder;
	float rollDelay = 5;
	float rollDuration = 1;
	static float rollElapsed = 0;
	float rollMovement = 512;

	if (rollElapsed == 0)
	{
		bol_RollFaceHolder = sta_Current.Facing;
	}

	if (rollElapsed > 0.25 && rollElapsed < 0.75)
	{
		sta_Current.Invincible = true;
	}
	else
	{
		sta_Current.Invincible = false;
	}

	switch (bol_RollFaceHolder)
	{
	case RIGHT:
		vec_Velocity.x += rollMovement * ElapsedTime;
		break;
	case LEFT:
		vec_Velocity.x -= rollMovement * ElapsedTime;
		break;
	}

	rollElapsed += ElapsedTime;
	if (rollElapsed >= rollDuration)
	{
		rollElapsed = 0;
		DisengageRoll();
	}
}
void EnemyObject::DisengageRoll()
{
	sta_Current.Rolling = false;
}

void EnemyObject::EngageBlock()
{
	sta_Current.Blocking = true;
}

void EnemyObject::DisengageBlock()
{
	sta_Current.Blocking = false;
}

void EnemyObject::EngageAttack(Attack attack, Player &player)
{
	if (attack.type == RANGE)
	{
		sta_Current.Shooting = true;

		// Delta X and Delta Y
		float dX = player.GetPosition().x - GetPosition().x;
		float dY = player.GetPosition().y - GetPosition().y;

		// Enemy Angle and offsets
		float anglePlayer = (atan2(dX, dY) * 180 / PI) + 180;
		float posOffset = attack.AngleOffset;
		float negOffset = -attack.AngleOffset;

		// Alter offsets if the angle passed in is too close to the 360/0 division
		if (flo_VisionAngle > 0 && flo_VisionAngle < posOffset)
		{
			negOffset += 360;
		}
		if (flo_VisionAngle > (360 - posOffset) && flo_VisionAngle < 360)
		{
			posOffset -= 360;
		}

		// Check LOS, then Range, then If it crits
		if (anglePlayer < (flo_VisionAngle + posOffset) && anglePlayer >(flo_VisionAngle + negOffset))
		{
			if ((dX * dX) + (dY * dY) <= (attack.Range * attack.Range) || (dX * dX) + (dY * dY) <= -(attack.Range * attack.Range))
			{
				player.dr_Input.Hit = true;
				float crit = getRandomNumber(0.0, 1.0);
				std::cout << crit << std::endl;

				if (crit < attack.CritChance)
				{
					player.dr_Input.Critical = true;
					//std::cout << "Critical Hit" << std::endl;
					float calcDmg = attack.Damage * attack.CritDamage;
					player.recieveDamage(calcDmg);
				}
				else
				{
					player.dr_Input.Critical = false;
					//std::cout << "Normal Attack" << std::endl;
					float calcDmg = attack.Damage;
					player.recieveDamage(calcDmg);
				}
			}
			else
			{
				player.dr_Input.Hit = false;
				//std::cout << "Target was not in range" << std::endl;
			}
		}
		else
		{
			player.dr_Input.Hit = false;
			//std::cout << "Target was not in sight" << std::endl;
		}
	}
	else if (attack.type == MELEE)
	{
		sta_Current.Meleeing = true;

		sf::RectangleShape hitbox;
		hitbox.setOrigin(sf::Vector2f(0, attack.TopOffset));
		hitbox.setPosition(GetPosition());

		if (sta_Current.Facing == LEFT)
		{
			hitbox.setSize(sf::Vector2f(-attack.Range, (attack.TopOffset + attack.BottomOffset)));
		}
		else
		{
			hitbox.setSize(sf::Vector2f(attack.Range, (attack.TopOffset + attack.BottomOffset)));
		}

		if (hitbox.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds()))
		{
			player.dr_Input.Hit = true;
			float crit = getRandomNumber(0.0, 1.0);
			std::cout << crit << std::endl;

			if (crit < attack.CritChance)
			{
				player.dr_Input.Critical = true;
				//std::cout << "Critical Hit" << std::endl;

				float calcDmg = attack.Damage * attack.CritDamage;
				player.dr_Input.TotalDmg = calcDmg;
				player.recieveDamage(calcDmg);
			}
			else
			{
				player.dr_Input.Critical = false;
				//std::cout << "Normal Attack" << std::endl;

				float calcDmg = attack.Damage;
				player.dr_Input.TotalDmg = calcDmg;
				player.recieveDamage(calcDmg);
			}
		}
		else
		{
			player.dr_Input.Hit = false;
			//std::cout << "Target was not in range" << std::endl;
		}
	}
}

void EnemyObject::ProcessAttack(float ElapsedTime, Attack attack)
{
	float attackDuration = attack.AttackSpeed;
	static float attackElapsed = 0;

	attackElapsed += ElapsedTime;
	if (attackElapsed >= attackDuration)
	{
		attackElapsed = 0;
		DisengageAttack();
	}
}

void EnemyObject::DisengageAttack()
{
	sta_Current.Shooting = false;
	sta_Current.Meleeing = false;
}

void EnemyObject::recieveDamage(float incomingDmg, DamageReport &report)
{
	if (sta_Current.Blocking == true)
	{
		incomingDmg = incomingDmg * att_Stats.Block;
	}
	if (sta_Current.Invincible == true)
	{
		incomingDmg = 0;
	}

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
	float reduct = ArmorReduction(att_Stats.Armor);
	float postArmorDmg = postShieldDmg * reduct;
	report.HealthDmg = postArmorDmg;
	flo_CurrentHealth -= postArmorDmg;
	sta_Current.TookDamage = true;
}