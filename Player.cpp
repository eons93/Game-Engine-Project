#include "stdafx.h"
#include "Player.h"
#include "Enumerations.h"
#include <iostream>


Player::Player()
{
	// Load image to texture then apply to Player's Sprite
	spr_CurrentSprite.setTexture(ani_CurrentAnimatation.txu_Source);
	spr_CurrentSprite.setTextureRect(ani_CurrentAnimatation.Animate());

	//Set Origin
	spr_CurrentSprite.setOrigin(sf::Vector2f(32, 32));

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
	bol_Facing = RIGHT;
	
	bol_Jumping = false;
	bol_Ducking = false;
	bol_Rolling = false;
	bol_Blocking = false;
	bol_Falling = false;
	bol_Shooting = false;
	bol_Meleeing = false;
	bol_MovingL = false;
	bol_MovingR = false;
	cs_CurrentState = CS_GROUND_FACE;


	//Set Stats
	flo_Move_Speed = 7.0;
	flo_Jump_Speed = 1.0;

	flo_JumpHeight = 128;
	flo_JumpDuration = 30;
	flo_JumpCounter = 0;
	bol_CanJump = true;

	int_RollDelay = 5;
	int_RollDuration = 30;
	int_RollCounter = 0;
	flo_RollMovement = 192;
}

// Updates player stats
void Player::UpdatePhase1()
{
	// Apply action effects
	Manager();
}

// applies updated player stats
void Player::UpdatePhase2()
{
	StateDetector();
	ReverseSprite();
	if (CompareState() == true)
	{
		ani_CurrentAnimatation = CurrentAnimationFunc();
	}
	spr_CurrentSprite.setTextureRect(ani_CurrentAnimatation.Animate());
	
	float dt = 0.5;

	if (bol_Falling == true)
	{
		vec_Velocity.y += GRAVITY * dt;
		vec_Position.x += vec_Velocity.x * dt;
		vec_Position.y += vec_Velocity.y * dt;

	}
	else
	{
		vec_Position.x += vec_Velocity.x * dt;
		vec_Position.y += vec_Velocity.y * dt;
	}
	vec_Velocity.x = 0;
	
	CheckMinMax(vec_Position, vec_Velocity);

	spr_CurrentSprite.setPosition(vec_Position);
	CopyState(cs_CurrentState);

	
	bol_Falling = true;
	
}

void Player::Spawn(Map map)
{
	vec_Position.x = map.vec_PlayerSpawn.x;
	vec_Position.y = map.vec_PlayerSpawn.y;

	ResetMinMax(vec_Position, vec_Velocity);
	
}




//------------Sprite and Animation------------------------

// Returns Sprite so that it can be drawn
sf::Sprite Player::GetSprite()
{
	return spr_CurrentSprite;
}

sf::Vector2f Player::GetPosition()
{
	return spr_CurrentSprite.getPosition();
}

//Flips Player Sprite if facing left. 
void Player::ReverseSprite()
{
	switch (bol_Facing) 
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
		//Block, 
		//IDLE

	if (bol_MovingL || bol_MovingR == true)
	{
		if (bol_Jumping == true)
		{
			cs_CurrentState = CS_JUMP;
		}
		else if (bol_Falling == true)
		{
			cs_CurrentState = CS_AIR;
		}
		else
		{
			cs_CurrentState = CS_GROUND_MOVING;
		}
	}
	else if (bol_Ducking == true)
	{
		if (bol_Rolling == true)
		{
			cs_CurrentState = CS_ROLL;
		}
		else
		{
			cs_CurrentState = CS_DUCK;
		}
	}
	else if (bol_Jumping == true)
	{
		cs_CurrentState = CS_JUMP;
	}
	else if (bol_Falling == true)
	{
		cs_CurrentState = CS_AIR;
	}
	else
	{
		cs_CurrentState = CS_GROUND_FACE;
	}
}

// Returns correct animation based on Complex State
Animation Player::CurrentAnimationFunc()
{
	
	switch (cs_CurrentState)
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

// changes player information based on State
void Player::Manager()
{
	if (bol_MovingL == true)
	{
		vec_Velocity.x -= flo_Move_Speed;
	}

	if (bol_MovingR == true)
	{
		vec_Velocity.x += flo_Move_Speed;
	}

	if (bol_Jumping == true)
	{
		ProcessJump();
	}

	if (bol_Rolling == true)
	{
		ProcessRoll();
	}
}



//---------------Misc Functions-----------------------------


void Player::CopyState(ComplexState holder)
{
	cs_StateHolder = holder;
	bol_FacingHolder = bol_Facing;
}

bool Player::CompareState()
{
	if (cs_StateHolder != cs_CurrentState)
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