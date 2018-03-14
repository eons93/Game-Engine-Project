#pragma once
#include <SFML\Graphics.hpp>

struct Attributes
{
	float Health;
	float Armor;
	float Shield;

	float MovementSpeed;


};

struct Attack
{
	float Damage;
	float AttackSpeed;
	float CriticalChance;
	float CriticalDamage;
	float Range;
};

struct Ability
{
	float Cooldown;
	float Range;
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