#include "stdafx.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include <iostream>


Player::Player()
{
	// Load Assets
	LoadAnimations();

	// Current Sprite
	spr_CurrentSprite.setTexture(ani_CurrentAnimatation.txu_Source);
	spr_CurrentSprite.setTextureRect(ani_CurrentAnimatation.Animate(0));
	spr_CurrentSprite.setOrigin(sf::Vector2f(32, 32));

	// Arm
	rec_Arm.setSize(sf::Vector2f(96, 4));
	rec_Arm.setOrigin(sf::Vector2f(2, 2));
	rec_Arm.setFillColor(sf::Color(255, 0, 255));
	rec_Arm.setOutlineThickness(-1);
	rec_Arm.setOutlineColor(sf::Color::White);
	//rec_Arm.setScale(-1.0, 1.0);

	//Set Default Position
	vec_Position.x = 500;
	vec_Position.y = 800;
	vec_Velocity.x = 0;
	vec_Velocity.y = 0;
	flo_MaxX = 0;
	flo_MinX = 0;
	flo_MaxY = 0;
	flo_MinY = 0;

	//Set Default states

	sta_Current.Facing = RIGHT;
	
	sta_Current.Jumping = false;
	sta_Current.Ducking = false;
	sta_Current.Rolling = false;
	sta_Current.Blocking = false;
	sta_Current.Falling = false;
	sta_Current.Shooting = false;
	sta_Current.Meleeing = false;
	sta_Current.MovingL = false;
	sta_Current.MovingR = false;
	sta_Current.CurrentState = CS_GROUND_FACE;
	sta_Current.CanJump = true;

	//Set Stats
	att_Stats.Health = 1000.0;
	att_Stats.Armor = 100;
	att_Stats.Shield = 100;
	att_Stats.MovementSpeed = 256.0;

	att_Stats.MeleeAttack.type = MELEE;
	att_Stats.MeleeAttack.Damage = 50;
	att_Stats.MeleeAttack.AttackSpeed = 1;
	att_Stats.MeleeAttack.CritChance = 0.1;
	att_Stats.MeleeAttack.CritDamage = 2.0;
	att_Stats.MeleeAttack.Range = BitConvert64(1.5);
	att_Stats.MeleeAttack.AngleOffset = 0;
	att_Stats.MeleeAttack.BottomOffset = 48;
	att_Stats.MeleeAttack.TopOffset = 48;

	att_Stats.RangeAttack.type = MELEE;
	att_Stats.RangeAttack.Damage = 50;
	att_Stats.RangeAttack.AttackSpeed = 1;
	att_Stats.RangeAttack.CritChance = 0.1;
	att_Stats.RangeAttack.CritDamage = 2.0;
	att_Stats.RangeAttack.Range = BitConvert64(1.5);
	att_Stats.RangeAttack.AngleOffset = 0;
	att_Stats.RangeAttack.BottomOffset = 48;
	att_Stats.RangeAttack.TopOffset = 48;


}

/*
// Updates player stats
void Player::UpdatePhase1(float ElapsedTime)
{
	// Apply action effects
	Manager(ElapsedTime);
}*/

// applies updated player stats
void Player::UpdatePlayer(float ElapsedTime, float angle)
{
	StateDetector();
	ReverseSprite();
	if (CompareState() == true)
	{
		ani_CurrentAnimatation = CurrentAnimationFunc();
	}
	spr_CurrentSprite.setTextureRect(ani_CurrentAnimatation.Animate(ElapsedTime));

	// Apply Gravity and Velocity to Position
	if (sta_Current.Falling == true)
	{
		vec_Velocity.y += GRAVITY * ElapsedTime;
		vec_Position.x += vec_Velocity.x;
		vec_Position.y += vec_Velocity.y;

	}
	else
	{
		vec_Position.x += vec_Velocity.x;
		vec_Position.y += vec_Velocity.y;
	}
	vec_Velocity.x = 0;
	CheckMinMax(vec_Position, vec_Velocity);


	spr_CurrentSprite.setPosition(vec_Position);
	CopyState(sta_Current.CurrentState);
	rec_Arm.setPosition(vec_Position);
	rec_Arm.setRotation(-angle - 90);
	
	sta_Current.Falling = true;
}

void Player::Spawn(Map map)
{
	vec_Position.x = map.vec_PlayerSpawn.x;
	vec_Position.y = map.vec_PlayerSpawn.y;

	ResetMinMax(vec_Position, vec_Velocity);
}

//------------Getters and Setters------------------------

sf::Sprite Player::GetSprite()
{
	return spr_CurrentSprite;
}

sf::RectangleShape Player::GetArm()
{
	return rec_Arm;
}

sf::Vector2f Player::GetPosition()
{
	return spr_CurrentSprite.getPosition();
}

sf::Vector2f Player::GetVelocity()
{
	return vec_Velocity;
}

States Player::GetState()
{
	return sta_Current;
}

Attributes Player::GetAttributes()
{
	return att_Stats;
}

float Player::GetCurrentHealth()
{
	return flo_CurrentHealth;
}


//--------------Update Sub Functions----------------

//Flips Player Sprite if facing left. 
void Player::ReverseSprite()
{
	switch (sta_Current.Facing)
	{
		case LEFT:
			spr_CurrentSprite.setScale(-1.f, 1.f);
			break;
		case RIGHT:
			spr_CurrentSprite.setScale(1.f, 1.f);
			break;
	}
}

// Analyzes state variables to assign Complex State
void Player::StateDetector()
{
	//Check Order:
		//Shoot (jump/fall, ground), 
		//Melee (jump/fall, ground), 
		//Moving (jump, fall, ground), 
		//Duck (rolling, not), 
		//Jump, 
		//Fall,
		//Block, 
		//IDLE

	if (sta_Current.Shooting == true)
	{
		if (sta_Current.Falling == true || sta_Current.Jumping == true)
		{
			sta_Current.CurrentState = CS_AIR_SHOOT;
		}
		else
		{
			sta_Current.CurrentState = CS_GROUND_SHOOT;
		}
	}
	else if (sta_Current.Meleeing == true)
	{
		if (sta_Current.Falling == true || sta_Current.Jumping == true)
		{
			sta_Current.CurrentState = CS_AIR_MELEE;
		}
		else
		{
			sta_Current.CurrentState = CS_GROUND_MELEE;
		}
	}

	else if (sta_Current.MovingL || sta_Current.MovingR == true)
	{
		if (sta_Current.Jumping == true)
		{
			sta_Current.CurrentState = CS_JUMP;
		}
		else if (sta_Current.Falling == true)
		{
			sta_Current.CurrentState = CS_AIR;
		}
		else
		{
			sta_Current.CurrentState = CS_GROUND_MOVING;
		}
	}
	else if (sta_Current.Ducking == true)
	{
		if (sta_Current.Rolling == true)
		{
			sta_Current.CurrentState = CS_ROLL;
		}
		else
		{
			sta_Current.CurrentState = CS_DUCK;
		}
	}
	else if (sta_Current.Jumping == true)
	{
		sta_Current.CurrentState = CS_JUMP;
	}
	else if (sta_Current.Falling == true)
	{
		sta_Current.CurrentState = CS_AIR;
	}
	else
	{
		sta_Current.CurrentState = CS_GROUND_FACE;
	}
}

// Returns correct animation based on Complex State
Animation Player::CurrentAnimationFunc()
{
	
	switch (sta_Current.CurrentState)
	{
	case CS_BLOCK:
		return ani_Block;
		break;
	case CS_JUMP:
		return ani_Jump;
		break;
	case CS_DUCK:
		return ani_Duck;
		break;
	case CS_ROLL:
		return ani_Roll;
		break;
	case CS_GROUND_FACE:
		return ani_Idle;
		break;
	case CS_GROUND_MOVING:
		return ani_Run;
		break;
	case CS_GROUND_SHOOT:
		return ani_Shoot;
		break;
	case CS_GROUND_MELEE:
		return ani_Melee;
		break;
	case CS_AIR:
		return ani_Fall;
		break;
	case CS_AIR_SHOOT:
		return ani_AirShoot;
		break;
	case CS_AIR_MELEE:
		return ani_AirMelee;
		break;
	}
}

/*
// Inputs States, outputs Actions
void Player::Manager(float ElapsedTime)
{
	if (sta_Current.MovingL == true)
	{
		vec_Velocity.x -= att_Stats.MovementSpeed * ElapsedTime;
	}

	if (sta_Current.MovingR == true)
	{
		vec_Velocity.x += att_Stats.MovementSpeed * ElapsedTime;
	}

	if (sta_Current.Jumping == true)
	{
		ProcessJump(ElapsedTime);
	}

	if (sta_Current.Rolling == true)
	{
		ProcessRoll(ElapsedTime);
	}
}*/

//---------------Misc Functions-----------------------------

void Player::CopyState(ComplexState holder)
{
	cs_StateHolder = holder;
	bol_FacingHolder = sta_Current.Facing;
}

bool Player::CompareState()
{
	if (cs_StateHolder != sta_Current.CurrentState)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::CheckMinMax(sf::Vector2f position, sf::Vector2f velocity)
{
	if (position.x < flo_MinX)
	{
		flo_MinX = position.x;
	}

	if (position.x > flo_MaxX)
	{
		flo_MaxX = position.x;
	}

	if (position.y < flo_MinY)
	{
		flo_MinY = position.y;
	}

	if (position.y > flo_MaxY)
	{
		flo_MaxY = position.y;
	}


	if (velocity.x < flo_MinVelX)
	{
		flo_MinVelX = velocity.x;
	}

	if (velocity.x > flo_MaxVelX)
	{
		flo_MaxVelX = velocity.x;
	}

	if (velocity.y < flo_MinVelY)
	{
		flo_MinVelY = velocity.y;
	}

	if (velocity.y > flo_MaxVelY)
	{
		flo_MaxVelY = velocity.y;
	}
}

void Player::ResetMinMax(sf::Vector2f position, sf::Vector2f velocity)
{
	flo_MinX = position.x;
	flo_MaxX = position.x;
	flo_MinY = position.y;
	flo_MaxY = position.y;

	flo_MinVelX = 0;
	flo_MinVelY = 0;
	flo_MaxVelX = 0;
	flo_MaxVelY = 0;
}