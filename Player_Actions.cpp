#include "stdafx.h"
#include "Player.h"
#include "GeneralFunctions.h"
#include <iostream>
#include <cmath>


// -------------------------------------MOVEMENT ACTIONS-------------------------------

// Right Movement Functions
void Player::MoveRight()
{
	sta_Current.MovingR = true;
}
void Player::StopRight()
{
	sta_Current.MovingR = false;
}

// Left Movement Functions
void Player::MoveLeft()
{
	sta_Current.MovingL = true;
}
void Player::StopLeft()
{
	sta_Current.MovingL = false;
}

// Jump Functions
void Player::EngageJump()
{
	sta_Current.Jumping = true;
	sta_Current.Falling = true;
	sta_Current.CanJump = false;
}
void Player::ProcessJump(float ElapsedTime)
{
	// Jump Action Stats
	float jumpSpeed = 40;
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
void Player::DisengageJump()
{
	sta_Current.Jumping = false;
}

// Duck Functions
void Player::EngageDuck()
{
	sta_Current.Ducking = true;
}
void Player::DisengageDuck()
{
	sta_Current.Ducking = false;
}

//------------------------------------COMBAT ACTIONS----------------------------------

// Roll Functions
void Player::EngageLeftRoll()
{
	sta_Current.Rolling = true;
	sta_Current.Facing = LEFT;
}
void Player::EngageRightRoll()
{
	sta_Current.Rolling = true;
	sta_Current.Facing = RIGHT;
}
void Player::ProcessRoll(float ElapsedTime)
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
void Player::DisengageRoll()
{
	sta_Current.Rolling = false;
}


void Player::EngageMelee(float angle, EnemyObject &enemy)
{
	sta_Current.Meleeing = true;
	Attack attack = att_Stats.MeleeAttack;

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
	
	if (hitbox.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds()))
	{
		dr_Holder.Hit = true;
		float crit = getRandomNumber(0.0, 1.0);
		std::cout << crit << std::endl;

		if (crit < attack.CritChance)
		{
			dr_Holder.Critical = true;
			std::cout << "Critical Hit" << std::endl;

			float calcDmg = attack.Damage * attack.CritDamage;
			dr_Holder.TotalDmg = calcDmg;
			enemy.recieveDamage(calcDmg, dr_Holder);
		}
		else
		{
			dr_Holder.Critical = false;
			std::cout << "Normal Attack" << std::endl;

			float calcDmg = attack.Damage;
			dr_Holder.TotalDmg = calcDmg;
			enemy.recieveDamage(calcDmg, dr_Holder);
		}
	}
	else
	{
		dr_Holder.Hit = false;
		std::cout << "Target was not in range" << std::endl;
	}
}

void Player::ProcessMelee(float ElapsedTime)
{
	Attack attack = att_Stats.MeleeAttack;
	float attackDuration = attack.AttackSpeed;
	static float attackElapsed = 0;

	attackElapsed += ElapsedTime;
	if (attackElapsed >= attackDuration)
	{
		attackElapsed = 0;
		DisengageMelee();
	}
}

void Player::DisengageMelee()
{
	sta_Current.Meleeing = false;
}

void Player::EngageRange(float angle, EnemyObject &enemy)
{
	sta_Current.Shooting = true;
	Attack attack = att_Stats.RangeAttack;

	// Delta X and Delta Y
	float dX = enemy.GetPosition().x - GetPosition().x;
	float dY = enemy.GetPosition().y - GetPosition().y;

	// Enemy Angle and offsets
	float angleEnemy = (atan2(dX, dY) * 180 / PI) + 180;
	float posOffset = attack.AngleOffset;
	float negOffset = -attack.AngleOffset;

	// Alter offsets if the angle passed in is too close to the 360/0 division
	if (angle > 0 && angle < posOffset)
	{
		negOffset += 360;
	}
	if (angle >(360 - posOffset) && angle < 360)
	{
		posOffset -= 360;
	}

	// Check LOS, then Range, then If it crits
	if (angleEnemy < (angle + posOffset) && angleEnemy >(angle + negOffset))
	{
		if ((dX * dX) + (dY * dY) <= (attack.Range * attack.Range) || (dX * dX) + (dY * dY) <= -(attack.Range * attack.Range))
		{
			dr_Holder.Hit = true;
			float crit = getRandomNumber(0.0, 1.0);
			std::cout << crit << std::endl;

			if (crit < attack.CritChance)
			{
				dr_Holder.Critical = true;
				std::cout << "Critical Hit" << std::endl;
				float calcDmg = attack.Damage * attack.CritDamage;
				enemy.recieveDamage(calcDmg, dr_Holder);
			}
			else
			{
				dr_Holder.Critical = false;
				std::cout << "Normal Attack" << std::endl;
				float calcDmg = attack.Damage;
				enemy.recieveDamage(calcDmg, dr_Holder);
			}
		}
		else
		{
			dr_Holder.Hit = false;
			std::cout << "Target was not in range" << std::endl;
		}
	}
	else
	{
		dr_Holder.Hit = false;
		std::cout << "Target was not in sight" << std::endl;
	}

}

void Player::ProcessRange(float ElapsedTime)
{
	Attack attack = att_Stats.RangeAttack;
	float attackDuration = attack.AttackSpeed;
	static float attackElapsed = 0;

	attackElapsed += ElapsedTime;
	if (attackElapsed >= attackDuration)
	{
		attackElapsed = 0;
		DisengageRange();
	}
}

void Player::DisengageRange()
{
	sta_Current.Shooting = false;
}