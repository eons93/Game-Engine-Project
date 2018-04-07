#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include <string>
#include "Structs.h"

class Map;
class Player;

using namespace sf;

class EnemyObject
{
private:
	
public:
	EnemyObject();

	//Drawn Objects
	sf::Text txt_Name;
	sf::RectangleShape rec_Background;
	sf::RectangleShape rec_CurrentHealth;
	sf::RectangleShape rec_CurrentShields;
	sf::RectangleShape rec_DamageFlasher;    //*******

	// Enemy Identification
	std::string str_Name;
	sf::Font fon_Enemy;
	int int_ID;

	// Enemy Stats
	EnemyAttributes att_Stats;
	float flo_CurrentHealth;
	float flo_CurrentShields;
	float flo_FinalDuration;                 //*******

	// Vision Stats
	float flo_VisionRange;
	float flo_VisionAngle;
	float flo_VisionOffset;

	// Drawing Managers
	sf::Sprite spr_CurrentSprite;
	Animation ani_Current_State_Animation;
	sf::Sprite spr_Arm;
	sf::Color SetFlasher(float ElapsedTime); //*******

	//Animation Managers
	void StateDetector();
	void ReverseSprite();
	Animation CurrentAnimationFunc();
	sf::Texture CurrentArmFunc();

	//State Memory
	void CopyState(ComplexState holder);
	bool CompareState();
	ComplexState cs_StateHolder;
	bool bol_FacingHolder;

	// Animations
	Animation ani_Idle;
	Animation ani_Death;
	Animation ani_Run;
	Animation ani_Melee;
	Animation ani_AirMelee;
	Animation ani_Jump;
	Animation ani_Fall;
	Animation ani_Roll;
	Animation ani_Duck;
	Animation ani_Block;

	// Enemy Arms
	sf::Texture txu_CurrentArm;
	sf::Texture txu_Firing;
	sf::Texture txu_Aiming;
	sf::Texture txu_NoShow;

	// Getters
	int GetID();
	sf::Sprite GetSprite();
	sf::Sprite GetArm();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	States GetState();
	EnemyAttributes GetAttributes();
	float GetCurrentHealth();
	float GetCurrentShields();

	// State Management
	States sta_Current;

	// Position Management
	sf::Vector2f vec_Position;
	sf::Vector2f vec_Velocity;
	void Spawn(int ID, Map map);

	// AI States
	bool CheckLOS(float playerAngle, float playerDistance);
	bool CheckLowHealth();
	bool CheckRange(float playerDistance);
	float CurrentHealthPercentage();
	float CalculateHealthLength();
	float CurrentShieldsPercentage();
	float CalculateShieldLength();
	AIState ais_CurrentState;

	//Enemy Actions
	void MoveLeft(float ElapsedTime);
	void MoveRight(float ElapsedTime);

	// Jumping
	void EngageJump();
	void ProcessJump(float ElapsedTime);
	void DisengageJump();

	// Ducking
	void EngageDuck();
	void DisengageDuck();

	// Rolling
	void EngageLeftRoll();
	void EngageRightRoll();
	void ProcessRoll(float ElapsedTime);
	void DisengageRoll();

	// Blocking
	void EngageBlock();
	void DisengageBlock();

	void EngageAttack(Attack attack, Player &player);
	void ProcessAttack(float ElapsedTime, Attack attack);
	void DisengageAttack();

	void recieveDamage(float incomingDmg, DamageReport &report);

	void Update(float ElapsedTime);
};