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
	Attributes att_Stats;
	float flo_CurrentHealth;

	// Drawing Manager
	sf::IntRect rec_Selection;
	sf::Sprite spr_CurrentSprite;
	sf::Texture txu_Texture;
	Animation ani_CurrentAnimatation;
	sf::RectangleShape rec_Arm;

	// Animation Manager 
	void LoadAnimations();
	void StateDetector();
	Animation CurrentAnimationFunc();
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
	
public:
	Player();

	// Getters
	sf::Sprite GetSprite();
	sf::RectangleShape GetArm();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	States GetState();
	Attributes GetAttributes();
	float GetCurrentHealth();
	DamageReport GetDamageReport();

	// State Management
	States sta_Current;

	// Position Management
	sf::Vector2f vec_Position;
	sf::Vector2f vec_Velocity;
	void Spawn(Map map);

	// Misc Variables
	DamageReport dr_Holder;

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

	// Melee Attack
	void EngageMelee(float angle, EnemyObject &enemy);
	void ProcessMelee(float ElapsedTime);
	void DisengageMelee();

	// Ranged Attack
	void EngageRange(float angle, EnemyObject &enemy);
	void ProcessRange(float ElapsedTime);
	void DisengageRange();

	// Updater
	void UpdatePlayer(float ElapsedTime, float angle);
};