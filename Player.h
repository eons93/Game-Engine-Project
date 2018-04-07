#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include "Structs.h"
#include "Enemy.h"


using namespace sf;

class Player
{

private:

	// Player's Stats
	PlayerAttributes att_Stats;
	float flo_CurrentHealth;
	float flo_CurrentShields;
	float flo_FinalDuration;

	// Drawing Manager
	sf::IntRect rec_Selection;
	sf::Sprite spr_CurrentSprite;
	sf::Texture txu_Texture;
	Animation ani_CurrentAnimatation;
	sf::Sprite spr_Arm;   
	sf::RectangleShape rec_DamageFlasher;
	sf::Color SetFlasher(float ElapsedTime);

	// Animation Manager 
	void LoadAnimations();
	void StateDetector();
	Animation CurrentAnimationFunc();
	sf::Texture CurrentArmFunc();   
	void ReverseSprite();

	// State Memory
	void CopyState(ComplexState holder);
	bool CompareState();
	ComplexState cs_StateHolder;
	bool bol_FacingHolder;

	// Player Animations
	Animation ani_Idle;
	Animation ani_Death;
	Animation ani_Run;
	Animation ani_Shoot;
	Animation ani_Melee;
	Animation ani_AirShoot;
	Animation ani_AirMelee;
	Animation ani_Jump;
	Animation ani_Fall;
	Animation ani_Roll;
	Animation ani_Duck;
	Animation ani_Block;

	//Player Arms
	sf::Texture txu_CurrentArm;     //**//
	sf::Texture txu_Firing;         //**//
	sf::Texture txu_Aiming;         //**//
	sf::Texture txu_NoShow;         //**//
	
public:
	Player();

	// Getters
	sf::Sprite GetSprite();
	sf::Sprite GetArm(); 
	sf::RectangleShape GetFlasher();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	States GetState();
	PlayerAttributes GetAttributes();
	float GetCurrentHealth();
	float GetCurrentShields();
	float GetFinalDuration();
	DamageReport GetDamageReport(bool type);

	// State Management
	States sta_Current;

	// Position Management
	sf::Vector2f vec_Position;
	sf::Vector2f vec_Velocity;
	void Spawn(Map map);

	// Misc Variables
	DamageReport dr_Output;
	DamageReport dr_Input;

	//----------------Player Actions------------------

	// Movement
	void MoveRight();
	void MoveLeft();
	void StopRight();
	void StopLeft();

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

	// Melee Attack
	void EngageMelee(float angle, EnemyObject &enemy);
	void ProcessMelee(float ElapsedTime);
	void DisengageMelee();

	// Ranged Attack
	void EngageRange(float angle, EnemyObject &enemy);
	void ProcessRange(float ElapsedTime);
	void DisengageRange();

	// Misc Combat
	void recieveDamage(float incomingDmg);

	// Updater
	void UpdatePlayer(float ElapsedTime, float angle);
};