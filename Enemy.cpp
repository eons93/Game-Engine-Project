#include "stdafx.h"
#include "Enemy.h"
#include "Enumerations.h"
#include <iostream>




EnemyObject::EnemyObject()
{
	name = "Blank";

	currentSprite.setOrigin(sf::Vector2f(32, 32));

	position.x = 64 * 14.5;
	position.y = 64 * 15;
	velocity.x = 0;
	velocity.y = 0;

	//Set Default states
	facing = RIGHT;

	jumping = false;
	ducking = false;
	rolling = false;
	blocking = false;
	falling = false;
	shooting = false;
	meleeing = false;
	movingL = false;
	movingR = false;
	currentState = GROUND_FACE;

}

void EnemyObject::Update()
{
	stateDetector();
	reverseSprite();
	if (compareState() == true)
	{
		currentState_Animation = currentAnimationFunc();
	}
	currentSprite.setTexture(currentState_Animation.source);
	currentSprite.setTextureRect(currentState_Animation.animate());

	float dt = 0.5;

	if (falling == true)
	{
		velocity.y += GRAVITY * dt;
		position.x += velocity.x * dt;
		position.y += velocity.y * dt;

	}
	else
	{
		position.x += velocity.x * dt;
		position.y += velocity.y * dt;
	}
	velocity.x = 0;

	currentSprite.setPosition(position);
	copyState(currentState);

	falling = true;
}

// Returns Sprite so that it can be drawn
sf::Sprite EnemyObject::getSprite()
{
	return currentSprite;
}

/*
void EnemyObject::spawn(int ID, Map map)
{
	position.x = map.EnemySpawn[ID].x;
	position.y = map.EnemySpawn[ID].y;

	Update();
}*/

void EnemyObject::stateDetector()
{
	//Check Order:
	//Shoot (jump/fall, ground), 
	//Melee (jump/fall, ground), 
	//Moving (jump, fall, ground), 
	//Duck (rolling, not), 
	//Jump, 
	//Block, 
	//IDLE

	if (movingL || movingR == true)
	{
		if (jumping == true)
		{
			currentState = C_JUMP;
		}
		else if (falling == true)
		{
			currentState = AIR;
		}
		else
		{
			currentState = GROUND_MOVING;
		}
	}
	else if (ducking == true)
	{
		if (rolling == true)
		{
			currentState = C_ROLL;
		}
		else
		{
			currentState = C_DUCK;
		}
	}
	else if (jumping == true)
	{
		currentState = C_JUMP;
	}
	else if (falling == true)
	{
		currentState = AIR;
	}
	else
	{
		currentState = GROUND_FACE;
	}
}

void EnemyObject::reverseSprite()
{
	switch (facing)
	{
	case LEFT:
		currentSprite.setScale(-1.f, 1.f);
		break;
	case RIGHT:
		currentSprite.setScale(1.f, 1.f);
		break;
	}
}

bool EnemyObject::compareState()
{
	if (stateHolder != currentState)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Animation EnemyObject::currentAnimationFunc()
{
	switch (currentState)
	{
	case AIR:
		return fall;
		break;
	case GROUND_FACE:
		return idle;
		break;
	case GROUND_MOVING:
		return run;
		break;
	}
}

void EnemyObject::copyState(ComplexState holder)
{
	stateHolder = holder;
	facingHolder = facing;
}