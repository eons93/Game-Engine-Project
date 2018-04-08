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

	// Arm Sprite
	spr_Arm.setTexture(txu_CurrentArm);                
	spr_Arm.setOrigin(sf::Vector2f(2, 2));            
	spr_Arm.setTextureRect(sf::IntRect(0, 0, 24, 4)); 
	
	// Damage Flasher Overlay
	rec_DamageFlasher.setOrigin(sf::Vector2f(32, 32));    
	rec_DamageFlasher.setSize(sf::Vector2f(64, 64));
	
	// Loader
	rec_Loader.setSize(sf::Vector2f(1000, 1000));
	rec_Loader.setOrigin(sf::Vector2f(500, 500));
	rec_Loader.setOutlineColor(sf::Color::Cyan);
	rec_Loader.setOutlineThickness(-1);

	//Set Default Position
	vec_Position.x = 500;
	vec_Position.y = 800;
	vec_Velocity.x = 0;
	vec_Velocity.y = 0;

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
	sta_Current.ArmState = AIMING;
	sta_Current.CurrentState = CS_GROUND_FACE;
	sta_Current.CanJump = true;
	sta_Current.Invincible = false;

	//Set Stats
	att_Stats.Health = 200.0;
	att_Stats.Armor = 100;
	att_Stats.Shield = 200.0;
	att_Stats.MovementSpeed = 256.0;
	att_Stats.Block = 0.1;
	att_Stats.Dodge = 1.5;

	flo_CurrentHealth = att_Stats.Health;
	flo_CurrentShields = att_Stats.Shield;
	flo_FinalDuration = 1;

	att_Stats.MeleeAttack.type = MELEE;
	att_Stats.MeleeAttack.Damage = 20;
	att_Stats.MeleeAttack.AttackSpeed = 1;
	att_Stats.MeleeAttack.CritChance = 0.1;
	att_Stats.MeleeAttack.CritDamage = 2.0;
	att_Stats.MeleeAttack.Range = X_64(1.5);
	att_Stats.MeleeAttack.AngleOffset = 0;
	att_Stats.MeleeAttack.BottomOffset = 48;
	att_Stats.MeleeAttack.TopOffset = 48;

	att_Stats.RangeAttack.type = RANGE;
	att_Stats.RangeAttack.Damage = 20;
	att_Stats.RangeAttack.AttackSpeed = 1;
	att_Stats.RangeAttack.CritChance = 0.2;
	att_Stats.RangeAttack.CritDamage = 2.0;
	att_Stats.RangeAttack.Range = X_64(5);
	att_Stats.RangeAttack.AngleOffset = 10;
	att_Stats.RangeAttack.BottomOffset = 0;
	att_Stats.RangeAttack.TopOffset = 0;


}

// applies updated player stats
void Player::UpdatePlayer(float ElapsedTime, float angle)
{
	// Determine Facing from angle of cursor
	if (angle > 0 && angle < 180)     
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
		ani_CurrentAnimatation = CurrentAnimationFunc();
	}
	sf::IntRect capture(ani_CurrentAnimatation.Animate(ElapsedTime));
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
	spr_CurrentSprite.setTextureRect(capture);
	txu_CurrentArm = CurrentArmFunc();   
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

	spr_CurrentSprite.setPosition(vec_Position);
	CopyState(sta_Current.CurrentState);
	spr_Arm.setPosition(vec_Position);            
	spr_Arm.setRotation(-angle - 90); 
	rec_DamageFlasher.setPosition(vec_Position);
	rec_DamageFlasher.setFillColor(SetFlasher(ElapsedTime));
	rec_Loader.setPosition(vec_Position);

	sta_Current.TookDamage = false;
	sta_Current.Falling = true;
	if (sta_Current.CurrentState == CS_DEAD)
	{
		flo_FinalDuration -= ElapsedTime;
	}
}

void Player::Spawn(Map map)
{
	vec_Position.x = map.vec_PlayerSpawn.x;
	vec_Position.y = map.vec_PlayerSpawn.y;
}


//------------Getters and Setters------------------------

sf::Sprite Player::GetSprite()
{
	return spr_CurrentSprite;
}

sf::Sprite Player::GetArm()
{
	return spr_Arm;
}

sf::RectangleShape Player::GetFlasher()
{
	return rec_DamageFlasher;
}

sf::RectangleShape Player::GetLoader()
{
	return rec_Loader;
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

PlayerAttributes Player::GetAttributes()
{
	return att_Stats;
}

float Player::GetCurrentHealth()
{
	return flo_CurrentHealth;
}

float Player::GetCurrentShields()
{
	return flo_CurrentShields;
}

float Player::GetFinalDuration()
{
	return flo_FinalDuration;
}

DamageReport Player::GetDamageReport(bool type)
{
	switch (type)
	{
	case OUTPUT:
		return dr_Output;
		break;
	case INPUT:
		return dr_Input;
		break;
	}
	
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
		//Death
		//Melee (jump/fall, ground), 
		//Duck (rolling, not),
		//Block, 
		//Jump, 
		//Fall,
		//Moving (jump, fall, ground), 
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

// Returns correct animation based on Complex State
Animation Player::CurrentAnimationFunc()
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

sf::Texture Player::CurrentArmFunc()
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

//---------------Misc Functions-----------------------------

sf::Color Player::SetFlasher(float ElapsedTime)          
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