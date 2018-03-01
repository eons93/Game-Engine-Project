#include "stdafx.h"
#include "Player.h"
#include <iostream>


// ---------------Movement Actions-------------------

// Right Movement Functions
void Player::moveRight()
{
	facing = RIGHT;
	movingR = true;
}
void Player::stopRight()
{
	movingR = false;
}

// Left Movement Functions
void Player::moveLeft()
{
	facing = LEFT;
	movingL = true;
}
void Player::stopLeft()
{
	movingL = false;
}

// Jump Functions
void Player::engageJump()
{
	jumping = true;
	falling = true;
	canJump = false;
}
void Player::processJump()
{
	velocity.y -= jumpSpeed;

	jumpCounter++;
	if (jumpCounter >= jumpDuration)
	{
		jumpCounter = 0;
		disengageJump();
	}
}
void Player::disengageJump()
{
	jumping = false;
}

// Duck Functions
void Player::engageDuck()
{
	ducking = true;
}
void Player::disengageDuck()
{
	ducking = false;
}

// Roll Functions
void Player::engageLeftRoll()
{
	rolling = true;
	facing = LEFT;
}
void Player::engageRightRoll()
{
	rolling = true;
	facing = RIGHT;
}
void Player::processRoll()
{
	if (rollCounter == 0)
	{
		rollFaceHolder = facing;
	}

	float rollFrame = rollMovement / rollDuration;

	switch (rollFaceHolder)
	{
	case RIGHT:
		velocity.x += rollFrame;
		break;
	case LEFT:
		velocity.x -= rollFrame;
		break;
	}

	rollCounter++;
	if (rollCounter >= rollDuration)
	{
		rollCounter = 0;
		DisengageRoll();
	}
}
void Player::DisengageRoll()
{
	rolling = false;
}