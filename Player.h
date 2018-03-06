#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"


using namespace sf;

class Player
{

private:

	// Player's Stats
	float flo_Move_Speed;
	float flo_Jump_Speed;

	// Jump Action Stats
	float flo_JumpHeight;
	int flo_JumpDuration;
	int flo_JumpCounter;
	
	// Roll Action Stats
	bool bol_RollFaceHolder;
	int int_RollDelay;
	int int_RollDuration;
	int int_RollCounter;
	float flo_RollMovement;
	
	// Manages what to draw
	sf::IntRect rec_Selection;
	sf::Sprite spr_CurrentSprite;
	sf::Texture txu_Texture;
	Animation ani_CurrentAnimatation;

	void ReverseSprite();

	//computes what the player class needs to do
	void Manager();
	
public:
	Player();

	// Manages what to draw. 
	void LoadAnimations();
	void StateDetector();
	Sprite GetSprite();
	sf::Vector2f GetPosition();
	Animation CurrentAnimationFunc();

	// Variables to Detect Player State
	bool bol_Facing;
	bool bol_Jumping;
	bool bol_Ducking;
	bool bol_Rolling;
	bool bol_Blocking;
	bool bol_Falling;
	bool bol_Shooting;
	bool bol_Meleeing;
	bool bol_MovingL;
	bool bol_MovingR;
	ComplexState cs_CurrentState;

	// Manages States
	void CopyState(ComplexState holder);
	bool CompareState();
	ComplexState cs_StateHolder;
	bool bol_FacingHolder;

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

	bool bol_CanJump;

	// Misc Stats
	sf::Vector2f vec_Position;
	sf::Vector2f vec_Velocity;
	void Spawn(Map map);
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


	//Player Actions
	void MoveRight();
	void MoveLeft();
	void StopRight();
	void StopLeft();

	void EngageJump();
	void ProcessJump();
	void DisengageJump();

	void EngageDuck();
	void DisengageDuck();

	void EngageLeftRoll();
	void EngageRightRoll();
	void ProcessRoll();
	void DisengageRoll();

	//Updater
	void UpdatePhase1();
	void UpdatePhase2();
};