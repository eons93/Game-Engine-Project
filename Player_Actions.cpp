#include "stdafx.h"
#include "Player.h"
#include <iostream>


// ---------------Movement Actions-------------------

// Right Movement Functions
void Player::MoveRight()
{
	sta_Current.Facing = RIGHT;
	sta_Current.MovingR = true;
}
void Player::StopRight()
{
	sta_Current.MovingR = false;
}

// Left Movement Functions
void Player::MoveLeft()
{
	sta_Current.Facing = LEFT;
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