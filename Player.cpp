#include "stdafx.h"
#include "Player.h"
#include "Enumerations.h"
#include <iostream>


Player::Player()
{
	// Load image to texture then apply to Player's Sprite
	current.setTexture(currentAnimatation.source);
	current.setTextureRect(currentAnimatation.animate());

	//Set Origin
	current.setOrigin(sf::Vector2f(32, 32));

	//Set Collision Data
	hitBox.collisionArea.setSize(sf::Vector2f(64, 64));
	hitBox.collisionArea.setOrigin(sf::Vector2f(32, 32));
	
	//Set Default Position
	position.x = 500;
	position.y = 800;
	velocity.x = 0;
	velocity.y = 0;
	maxX = 0;
	minX = 0;
	maxY = 0;
	minY = 0;

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


	//Set Stats
	moveSpeed = 7.0;
	angle = 0;
	jumpSpeed = 1.0;

	jumpHeight = 128;
	jumpDuration = 30;
	jumpCounter = 0;
	canJump = true;

	rollDelay = 5;
	rollDuration = 30;
	rollCounter = 0;
	rollMovement = 192;
}

// Updates player stats
void Player::updateStage1()
{
	// Apply action effects
	manager();
}

// applies updated player stats
void Player::updateStage2()
{
	stateDetector();
	reverseSprite();
	if (compareState() == true)
	{
		attachAnimation(currentAnimation());
	}
	current.setTextureRect(currentAnimatation.animate());
	
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
	
	checkMinMax(position, velocity);

	current.setPosition(position);
	hitBox.collisionArea.setPosition(position.x, position.y);
	copyState(currentState);

	
	falling = true;
	
}

void Player::spawn(Map map)
{
	position.x = map.playerSpawn.x;
	position.y = map.playerSpawn.y;

	resetMinMax(position, velocity);
	
}




//------------Sprite and Animation------------------------

// binds a different animation to Player
void Player::attachAnimation(Animation _new)
{
	currentAnimatation = _new;
}

// Returns Sprite so that it can be drawn
sf::Sprite Player::getSprite()
{
	return current;
}

sf::Vector2f Player::getPosition()
{
	return current.getPosition();
}

//Flips Player Sprite if facing left. 
void Player::reverseSprite()
{
	switch (facing) 
	{
		case LEFT:
			current.setScale(-1.f, 1.f);
			break;
		case RIGHT:
			current.setScale(1.f, 1.f);
			break;
	}
}

// Analyzes state variables to assign Complex State
void Player::stateDetector()
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

// Returns correct animation based on Complex State
Animation Player::currentAnimation()
{
	
	switch (currentState)
	{
	case C_BLOCK:
		return block;
		break;
	case C_JUMP:
		return jump;
		break;
	case C_DUCK:
		return duck;
		break;
	case C_ROLL:
		return roll;
		break;
	case GROUND_FACE:
		return idle;
		break;
	case GROUND_MOVING:
		return run;
		break;
	case GROUND_SHOOT:
		return shoot;
		break;
	case GROUND_MELEE:
		return melee;
		break;
	case AIR:
		return fall;
		break;
	case AIR_SHOOT:
		return airShoot;
		break;
	case AIR_MELEE:
		return airMelee;
		break;
	}
}

// changes player information based on State
void Player::manager()
{
	if (movingL == true)
	{
		velocity.x -= cos(angle) * moveSpeed;
		velocity.y += sin(angle) * moveSpeed;
	}

	if (movingR == true)
	{
		velocity.x += cos(angle) * moveSpeed;
		velocity.y -= sin(angle) * moveSpeed;
	}

	if (jumping == true)
	{
		processJump();
	}

	if (rolling == true)
	{
		processRoll();
	}
}



//---------------Misc Functions-----------------------------


void Player::copyState(ComplexState holder)
{
	stateHolder = holder;
	facingHolder = facing;
}

bool Player::compareState()
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

void Player::checkMinMax(sf::Vector2f position, sf::Vector2f velocity)
{
	if (position.x < minX)
	{
		minX = position.x;
	}

	if (position.x > maxX)
	{
		maxX = position.x;
	}

	if (position.y < minY)
	{
		minY = position.y;
	}

	if (position.y > maxY)
	{
		maxY = position.y;
	}


	if (velocity.x < minVelX)
	{
		minVelX = velocity.x;
	}

	if (velocity.x > maxVelX)
	{
		maxVelX = velocity.x;
	}

	if (velocity.y < minVelY)
	{
		minVelY = velocity.y;
	}

	if (velocity.y > maxVelY)
	{
		maxVelY = velocity.y;
	}
}

void Player::resetMinMax(sf::Vector2f position, sf::Vector2f velocity)
{
	minX = position.x;
	maxX = position.x;
	minY = position.y;
	maxY = position.y;

	minVelX = 0;
	minVelY = 0;
	maxVelX = 0;
	maxVelY = 0;
}