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
	txt_Name.setCharacterSize(12);
	txt_Name.setFillColor(sf::Color::White);

	rec_Background.setFillColor(sf::Color::Black);
	rec_Background.setSize(sf::Vector2f(48, 4));
	rec_CurrentHealth.setFillColor(sf::Color::Red);
	rec_CurrentHealth.setSize(sf::Vector2f(48, 4));

	spr_CurrentSprite.setOrigin(sf::Vector2f(32, 32));
	rec_DamageFlasher.setOrigin(sf::Vector2f(32, 32));
	rec_DamageFlasher.setSize(sf::Vector2f(64, 64));

	vec_Position.x = 64 * 14.5;
	vec_Position.y = 64 * 15;
	vec_Velocity.x = 0;
	vec_Velocity.y = 0;

	flo_FinalDuration = 1;

	//Set Default states
	sta_Current.TookDamage = false;
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
}

void EnemyObject::Update(float ElapsedTime)
{
	

	StateDetector();
	ReverseSprite();
	if (CompareState() == true)
	{
		ani_Current_State_Animation = CurrentAnimationFunc();
	}
	spr_CurrentSprite.setTexture(ani_Current_State_Animation.txu_Source);
	spr_CurrentSprite.setTextureRect(ani_Current_State_Animation.Animate(ElapsedTime));

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

	rec_DamageFlasher.setFillColor(SetFlasher(ElapsedTime));

	// Sprite and Name
	spr_CurrentSprite.setPosition(vec_Position);
	rec_DamageFlasher.setPosition(vec_Position);
	txt_Name.setString(str_Name);
	txt_Name.setOrigin(sf::Vector2f(txt_Name.getGlobalBounds().width / 2, txt_Name.getGlobalBounds().height * 2));
	txt_Name.setPosition(sf::Vector2f(spr_CurrentSprite.getPosition().x, spr_CurrentSprite.getPosition().y - 40));

	// Health Bar
	rec_Background.setOrigin(sf::Vector2f(rec_Background.getGlobalBounds().width / 2, rec_Background.getGlobalBounds().height * 2));
	rec_Background.setPosition(sf::Vector2f(spr_CurrentSprite.getPosition().x, spr_CurrentSprite.getPosition().y - 32));
	
	rec_CurrentHealth.setPosition(sf::Vector2f(rec_Background.getGlobalBounds().left, rec_Background.getGlobalBounds().top));
	if (CalculateHealthLength() < 0)
	{
		rec_CurrentHealth.setSize(sf::Vector2f(0, 4));
	}
	else
	{
		rec_CurrentHealth.setSize(sf::Vector2f(CalculateHealthLength(), 4));
	}
	

	CopyState(sta_Current.CurrentState);
	sta_Current.TookDamage = false;
	sta_Current.Falling = true;

	if (sta_Current.CurrentState == CS_DEAD)
	{
		flo_FinalDuration -= ElapsedTime;
	}
}

// Getters
int EnemyObject::GetID()
{
	return int_ID;
}

sf::Sprite EnemyObject::GetSprite()
{
	return spr_CurrentSprite;
}

sf::Vector2f EnemyObject::GetPosition()
{
	return vec_Position;
}

sf::Vector2f EnemyObject::GetVelocity()
{
	return vec_Velocity;
}

States EnemyObject::GetState()
{
	return sta_Current;
}

Attributes EnemyObject::GetAttributes()
{
	return att_Stats;
}

float EnemyObject::GetCurrentHealth()
{
	return flo_CurrentHealth;
}


void EnemyObject::Spawn(int ID, Map map)
{
	vec_Position.x = map.vec_EnemySpawn[ID].x;
	vec_Position.y = map.vec_EnemySpawn[ID].y;
}

float EnemyObject::CurrentHealthPercentage()
{
	float percentHealth = (flo_CurrentHealth * 100) / att_Stats.Health;
	return percentHealth;
}

float EnemyObject::CalculateHealthLength()
{
	float input = CurrentHealthPercentage();
	float output = (input * 48) / 100;
	return output;
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

	if (flo_CurrentHealth <= 0)
	{
		sta_Current.CurrentState = CS_DEAD;
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

void EnemyObject::ReverseSprite()
{
	//flo_CurrentHealth -= .1;
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

bool EnemyObject::CompareState()
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

Animation EnemyObject::CurrentAnimationFunc()
{
	switch (sta_Current.CurrentState)
	{
	case CS_DEAD:
		return ani_Death;
		break;
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

sf::Color EnemyObject::SetFlasher(float ElapsedTime)
{
	static float flasherCounter = 1.1;
	float flasherDuration = 1;
	sf::Color flasherColor(0, 0, 0, 0);

	if (flasherCounter < flasherDuration)
	{
		flasherCounter += ElapsedTime;
		flasherColor.r = (1 - flasherCounter) * 255;
		flasherColor.a = 63;
	}
	else if (sta_Current.TookDamage == true)
	{
		flasherCounter = 0;
		flasherColor.r = 255;
		flasherColor.a = 63;
	}
	else
	{
		//flasherCounter = 0;
		flasherColor.r = 0;
		flasherColor.a = 0;
	}
	return flasherColor;
}

void EnemyObject::CopyState(ComplexState holder)
{
	cs_StateHolder = holder;
	bol_FacingHolder = sta_Current.Facing;
}

bool EnemyObject::CheckLOS()
{
	return false;
}

bool EnemyObject::CheckLowHealth()
{
	return false;
}

bool EnemyObject::CheckRange()
{
	return false;
}