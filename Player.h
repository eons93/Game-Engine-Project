#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include "Structs.h"


using namespace sf;

class Player
{

private:

	// Player's Stats
	Attributes Att_Stats;
	float flo_CurrentHealth;

	// Drawing Manager
	sf::IntRect rec_Selection;
	sf::Sprite spr_CurrentSprite;
	sf::Texture txu_Texture;
	Animation ani_CurrentAnimatation;

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
	
	// Action Manager
	void Manager(float ElapsedTime);

	// Player Animations
	Animation ani_Idle;
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
	Sprite GetSprite();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	States GetState();
	Attributes GetAttributes();
	float GetCurrentHealth();

	// State Management
	States sta_Current;

	// Position Management
	sf::Vector2f vec_Position;
	sf::Vector2f vec_Velocity;
	void Spawn(Map map);

	// Misc Stats
	float flo_MaxX;
	float flo_MaxY;
	float flo_MinX;
	float flo_MinY;
	float flo_MinVelX;
	float flo_MaxVelX;
	float flo_MinVelY;
	float flo_MaxVelY;
	void CheckMinMax(sf::Vector2f position, sf::Vector2f velocity);
	void ResetMinMax(sf::Vector2f position, sf::Vector2f velocity);
	 
	// Player Actions

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

	// Updater
	void UpdatePhase1(float ElapsedTime);
	void UpdatePhase2(float ElapsedTime);
};