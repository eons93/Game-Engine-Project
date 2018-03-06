#include "stdafx.h"
#include "Enemy.h"
#include "Enumerations.h"
#include <iostream>




EnemyObject::EnemyObject()
{
	str_Name = "Blank";

	if (!fon_Enemy.loadFromFile("The Citadels.otf"))
	{
		std::cout << "Default Font not loaded" << std::endl;
	}
	txt_Name.setFont(fon_Enemy);
	txt_Name.setCharacterSize(16);
	txt_Name.setFillColor(sf::Color::White);
	txt_Name.setOrigin(sf::Vector2f(-txt_Name.getGlobalBounds().width * 2, txt_Name.getGlobalBounds().height));

	spr_CurrentSprite.setOrigin(sf::Vector2f(32, 32));

	vec_Position.x = 64 * 14.5;
	vec_Position.y = 64 * 15;
	vec_Velocity.x = 0;
	vec_Velocity.y = 0;

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

}

void EnemyObject::Update()
{
	StateDetector();
	ReverseSprite();
	if (CompareState() == true)
	{
		ani_Current_State_Animation = CurrentAnimationFunc();
	}
	spr_CurrentSprite.setTexture(ani_Current_State_Animation.txu_Source);
	spr_CurrentSprite.setTextureRect(ani_Current_State_Animation.Animate());

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

	spr_CurrentSprite.setPosition(vec_Position);
	txt_Name.setString(str_Name);
	txt_Name.setOrigin(sf::Vector2f(txt_Name.getGlobalBounds().width / 2, txt_Name.getGlobalBounds().height * 2));
	txt_Name.setPosition(sf::Vector2f(spr_CurrentSprite.getPosition().x, spr_CurrentSprite.getPosition().y - 32));
	CopyState(cs_CurrentState);

	bol_Falling = true;
}

// Returns Sprite so that it can be drawn
sf::Sprite EnemyObject::GetSprite()
{
	return spr_CurrentSprite;
}


void EnemyObject::Spawn(int ID, Map map)
{
	vec_Position.x = map.vec_EnemySpawn[ID].x;
	vec_Position.y = map.vec_EnemySpawn[ID].y;

	

	//Update();
}

void EnemyObject::StateDetector()
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

void EnemyObject::ReverseSprite()
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

bool EnemyObject::CompareState()
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

Animation EnemyObject::CurrentAnimationFunc()
{
	switch (cs_CurrentState)
	{
	case CS_AIR:
		return ani_Fall;
		break;
	case CS_GROUND_FACE:
		return ani_Idle;
		break;
	case CS_GROUND_MOVING:
		return ani_Run;
		break;
	}
}

void EnemyObject::CopyState(ComplexState holder)
{
	cs_StateHolder = holder;
	bol_FacingHolder = bol_Facing;
}