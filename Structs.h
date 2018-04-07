#pragma once
#include <SFML\Graphics.hpp>



struct LinearFunc
{
	float Slope;
	float Intercept;
};

struct ParabolicFunc
{
	float Y_Scale;
	float X_Scale;
	float Intercept;
};

struct Attack
{
	bool type;
	float Damage;
	float AttackSpeed;
	float CritChance;
	float CritDamage;
	float Range;
	float AngleOffset;
	float TopOffset;
	float BottomOffset;
};

struct Ability
{
	float Cooldown;
	float Range;
};

struct PlayerAttributes
{
	float Health;
	float Armor;
	float Shield;

	float MovementSpeed;

	float Block;
	float Dodge;

	Attack MeleeAttack;
	Attack RangeAttack;

};

struct EnemyAttributes
{
	float Health;
	float Armor;
	float Shield;

	float MovementSpeed;

	float Block;
	float Dodge;

	Attack Attack[3];

};

struct States
{
	bool Facing;
	bool Jumping;
	bool Ducking;
	bool Rolling;
	bool Blocking;
	bool Falling;
	bool Shooting;
	bool Meleeing;
	bool MovingL;
	bool MovingR;
	ArmState ArmState;
	ComplexState CurrentState;
	bool CanJump;
	bool TookDamage;
	bool Invincible;
};

struct DamageReport
{
	float TotalDmg;
	float ShieldDmg;
	float HealthDmg;
	bool Critical;
	bool Hit;

};