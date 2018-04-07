#include "stdafx.h"
#include "Enemy.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Player.h"
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
	rec_Background.setSize(sf::Vector2f(48, 8));
	rec_CurrentHealth.setFillColor(sf::Color::Red);
	rec_CurrentHealth.setSize(sf::Vector2f(48, 4));
	rec_CurrentShields.setFillColor(sf::Color(0, 64, 255));
	rec_CurrentShields.setSize(sf::Vector2f(48, 4));

	spr_CurrentSprite.setOrigin(sf::Vector2f(32, 32));
	rec_DamageFlasher.setOrigin(sf::Vector2f(32, 32));     //*******
	rec_DamageFlasher.setSize(sf::Vector2f(64, 64));        //*******
	 
	spr_Arm.setTexture(txu_CurrentArm);                
	spr_Arm.setOrigin(sf::Vector2f(2, 2));             

	vec_Position.x = 64 * 14.5;
	vec_Position.y = 64 * 15;
	vec_Velocity.x = 0;
	vec_Velocity.y = 0;

	flo_FinalDuration = 1;                                 //*******

	flo_VisionAngle = 90;
	flo_VisionRange = X_64(6);
	flo_VisionOffset = 5;

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
	sta_Current.ArmState = AIMING;
	sta_Current.CurrentState = CS_GROUND_FACE;
	sta_Current.Invincible = false;
}

void EnemyObject::Update(float ElapsedTime)
{
	// Determine Facing from angle of cursor
	if (flo_VisionAngle > 0 && flo_VisionAngle < 180) 
	{
		sta_Current.Facing = LEFT;
	}
	else                              
	{
		sta_Current.Facing = RIGHT;
	}
	ReverseSprite();


	StateDetector();
	if (CompareState() == true)
	{
		ani_Current_State_Animation = CurrentAnimationFunc();
	}
	sf::IntRect capture(ani_Current_State_Animation.Animate(ElapsedTime));
	if (sta_Current.Ducking == true)
	{
		capture.height = capture.height / 2;
		spr_CurrentSprite.setOrigin(32, 0);
		rec_DamageFlasher.setOrigin(32, 0);
		rec_DamageFlasher.setSize(sf::Vector2f(64, 32));
	}
	else
	{
		spr_CurrentSprite.setOrigin(32, 32);
		rec_DamageFlasher.setOrigin(32, 32);
		rec_DamageFlasher.setSize(sf::Vector2f(64, 64));
	}
	spr_CurrentSprite.setTexture(ani_Current_State_Animation.txu_Source);
	spr_CurrentSprite.setTextureRect(ani_Current_State_Animation.Animate(ElapsedTime));
	txu_CurrentArm = CurrentArmFunc();  
	spr_Arm.setTexture(txu_CurrentArm);
	spr_Arm.setTextureRect(sf::IntRect(0, 0, 48, 4));
	 
	

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

	// Place Health and Shields within limits
	if (flo_CurrentHealth > att_Stats.Health)
	{
		flo_CurrentHealth = att_Stats.Health;
	}
	if (flo_CurrentShields > att_Stats.Shield)
	{
		flo_CurrentShields = att_Stats.Shield;
	}


	// Sprite and Name
	spr_CurrentSprite.setPosition(vec_Position);
	rec_DamageFlasher.setPosition(vec_Position); 
	rec_DamageFlasher.setFillColor(SetFlasher(ElapsedTime));
	txt_Name.setString(str_Name);
	txt_Name.setOrigin(sf::Vector2f(txt_Name.getGlobalBounds().width / 2, txt_Name.getGlobalBounds().height * 2));
	txt_Name.setPosition(sf::Vector2f(spr_CurrentSprite.getPosition().x, spr_CurrentSprite.getPosition().y - 42));

	// Health Bar
	rec_Background.setOrigin(sf::Vector2f(rec_Background.getGlobalBounds().width / 2, rec_Background.getGlobalBounds().height * 2));
	rec_Background.setPosition(sf::Vector2f(spr_CurrentSprite.getPosition().x, spr_CurrentSprite.getPosition().y - 28));
	
	rec_CurrentHealth.setPosition(sf::Vector2f(rec_Background.getGlobalBounds().left, rec_Background.getGlobalBounds().top + 4));
	rec_CurrentHealth.setFillColor(HealthPercentColor(CurrentHealthPercentage()));
	if (CalculateHealthLength() < 0)
	{
		rec_CurrentHealth.setSize(sf::Vector2f(0, 4));
	}
	else
	{
		rec_CurrentHealth.setSize(sf::Vector2f(CalculateHealthLength(), 4));
	}
	// Shield Bar
	rec_CurrentShields.setPosition(sf::Vector2f(rec_Background.getGlobalBounds().left, rec_Background.getGlobalBounds().top));
	rec_CurrentShields.setFillColor(ShieldPercentColor(CurrentShieldsPercentage()));
	if (CalculateShieldLength() < 0)
	{
		rec_CurrentShields.setSize(sf::Vector2f(0, 4));
	}
	else
	{
		rec_CurrentShields.setSize(sf::Vector2f(CalculateShieldLength(), 4));
	}
	

	CopyState(sta_Current.CurrentState);
	spr_Arm.setPosition(vec_Position);            
	spr_Arm.setRotation(-flo_VisionAngle - 90);

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

sf::Sprite EnemyObject::GetArm()
{
	return spr_Arm;
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

EnemyAttributes EnemyObject::GetAttributes()
{
	return att_Stats;
}

float EnemyObject::GetCurrentHealth()
{
	return flo_CurrentHealth;
}

float EnemyObject::GetCurrentShields()
{
	return flo_CurrentShields;
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

float EnemyObject::CurrentShieldsPercentage()
{
	float percentShields = (flo_CurrentShields * 100) / att_Stats.Shield;
	return percentShields;
}

float EnemyObject::CalculateShieldLength()
{
	float input = CurrentShieldsPercentage();
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
	else if (sta_Current.Meleeing == true)
	{
		if (sta_Current.Falling == true || sta_Current.Jumping == true)
		{
			sta_Current.CurrentState = CS_AIR_MELEE;
			sta_Current.ArmState = NOSHOW;
		}
		else
		{
			sta_Current.CurrentState = CS_GROUND_MELEE;
			sta_Current.ArmState = NOSHOW;
		}
	}
	else if (sta_Current.Ducking == true)
	{
		if (sta_Current.Rolling == true)
		{
			sta_Current.CurrentState = CS_ROLL;
			sta_Current.ArmState = NOSHOW;
		}
		else
		{
			sta_Current.CurrentState = CS_DUCK;
			sta_Current.ArmState = AIMING;
		}
	}
	else if (sta_Current.Blocking == true)
	{
		sta_Current.CurrentState = CS_BLOCK;
		sta_Current.ArmState = NOSHOW;
	}
	else if (sta_Current.MovingL || sta_Current.MovingR == true)
	{
		if (sta_Current.Jumping == true)
		{
			sta_Current.CurrentState = CS_JUMP;
			sta_Current.ArmState = AIMING;
		}
		else if (sta_Current.Falling == true)
		{
			sta_Current.CurrentState = CS_AIR;
			sta_Current.ArmState = AIMING;
		}
		else
		{
			sta_Current.CurrentState = CS_GROUND_MOVING;
			sta_Current.ArmState = AIMING;
		}
	}
	else if (sta_Current.Jumping == true)
	{
		sta_Current.CurrentState = CS_JUMP;
		sta_Current.ArmState = AIMING;
	}
	else if (sta_Current.Falling == true)
	{
		sta_Current.CurrentState = CS_AIR;
		sta_Current.ArmState = AIMING;
	}
	else
	{
		sta_Current.CurrentState = CS_GROUND_FACE;
		sta_Current.ArmState = AIMING;
	}

	if (sta_Current.Shooting == true && sta_Current.ArmState != NOSHOW)
	{
		sta_Current.ArmState = FIRING;
	}
}

void EnemyObject::ReverseSprite()
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
	case CS_GROUND_MELEE:
		return ani_Melee;
		break;
	case CS_AIR:
		return ani_Fall;
		break;
	case CS_AIR_MELEE:
		return ani_AirMelee;
		break;
	}
}

sf::Texture EnemyObject::CurrentArmFunc()
{
	switch (sta_Current.ArmState)
	{
	case NOSHOW:
		return txu_NoShow;
		break;
	case FIRING:
		return txu_Firing;
		break;
	case AIMING:
		return txu_Aiming;
		break;
	}
}

sf::Color EnemyObject::SetFlasher(float ElapsedTime)          //*******
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

bool EnemyObject::CheckLOS(float playerAngle, float playerDistance)
{
	//float anglePlayer = AngleOf(GetPosition(), player.GetPosition());
	float visionBounds1 = flo_VisionAngle + flo_VisionOffset;
	float VisionBounds2 = flo_VisionAngle - flo_VisionOffset;

	if (playerAngle <= visionBounds1 && playerAngle >= VisionBounds2)
	{
		//float distancePlayer = DistanceOf(GetPosition(), player.GetPosition());

		if (playerDistance <= flo_VisionRange)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool EnemyObject::CheckLowHealth()
{
	if (GetCurrentHealth() < (0.1 * att_Stats.Health))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnemyObject::CheckRange(float playerDistance)
{
	float maxRange;

	// Determine Attack with Largest Attack Range
	if (att_Stats.Attack[0].Range > att_Stats.Attack[1].Range
		&& att_Stats.Attack[0].Range > att_Stats.Attack[2].Range)
	{
		maxRange = att_Stats.Attack[0].Range;
	}
	else if (att_Stats.Attack[1].Range > att_Stats.Attack[2].Range)
	{
		maxRange = att_Stats.Attack[1].Range;
	}
	else
	{
		maxRange = att_Stats.Attack[2].Range;
	}

	//Print(StringConvert(maxRange));

	// Determine if Player is within Range of Largest Attack Range
	if (playerDistance <= maxRange)
	{
		return true;
	}
	else
	{
		return false;
	}
}