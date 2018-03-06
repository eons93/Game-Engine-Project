#include "stdafx.h"
#include "Player.h"
#include <iostream>


// ---------------Movement Actions-------------------

// Right Movement Functions
void Player::MoveRight()
{
	bol_Facing = RIGHT;
	bol_MovingR = true;
}
void Player::StopRight()
{
	bol_MovingR = false;
}

// Left Movement Functions
void Player::MoveLeft()
{
	bol_Facing = LEFT;
	bol_MovingL = true;
}
void Player::StopLeft()
{
	bol_MovingL = false;
}

// Jump Functions
void Player::EngageJump()
{
	bol_Jumping = true;
	bol_Falling = true;
	bol_CanJump = false;
}
void Player::ProcessJump()
{
	vec_Velocity.y -= flo_Jump_Speed;

	flo_JumpCounter++;
	if (flo_JumpCounter >= flo_JumpDuration)
	{
		flo_JumpCounter = 0;
		DisengageJump();
	}
}
void Player::DisengageJump()
{
	bol_Jumping = false;
}

// Duck Functions
void Player::EngageDuck()
{
	bol_Ducking = true;
}
void Player::DisengageDuck()
{
	bol_Ducking = false;
}

// Roll Functions
void Player::EngageLeftRoll()
{
	bol_Rolling = true;
	bol_Facing = LEFT;
}
void Player::EngageRightRoll()
{
	bol_Rolling = true;
	bol_Facing = RIGHT;
}
void Player::ProcessRoll()
{
	if (int_RollCounter == 0)
	{
		bol_RollFaceHolder = bol_Facing;
	}

	float rollFrame = flo_RollMovement / int_RollDuration;

	switch (bol_RollFaceHolder)
	{
	case RIGHT:
		vec_Velocity.x += rollFrame;
		break;
	case LEFT:
		vec_Velocity.x -= rollFrame;
		break;
	}

	int_RollCounter++;
	if (int_RollCounter >= int_RollDuration)
	{
		int_RollCounter = 0;
		DisengageRoll();
	}
}
void Player::DisengageRoll()
{
	bol_Rolling = false;
}