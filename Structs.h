#pragma once
#include <SFML\Graphics.hpp>



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

struct Attributes
{
	float Health;
	float Armor;
	float Shield;

	float MovementSpeed;

	Attack MeleeAttack;
	Attack RangeAttack;

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
	ComplexState CurrentState;
	bool CanJump;
	bool TookDamage;
};

struct DamageReport
{
	float TotalDmg;
	float ShieldDmg;
	float HealthDmg;
	bool Critical;
	bool Hit;

};