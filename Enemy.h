#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include <string>
#include "Structs.h"

class Map;

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

	// Enemy Identification
	std::string str_Name;
	sf::Font fon_Enemy;
	int int_ID;

	// Enemy Stats
	Attributes att_Stats;
	float flo_CurrentHealth;

	// Drawing Managers
	sf::Sprite spr_CurrentSprite;
	Animation ani_Current_State_Animation;

	//Animation Managers
	void StateDetector();
	void ReverseSprite();
	Animation CurrentAnimationFunc();

	//State Memory
	void CopyState(ComplexState holder);
	bool CompareState();
	ComplexState cs_StateHolder;
	bool bol_FacingHolder;

	// Animations
	Animation ani_Idle;
	Animation ani_Run;
	Animation ani_Fall;

	// Getters
	int GetID();
	sf::Sprite GetSprite();
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
	void Spawn(int ID, Map map);

	// AI States
	bool CheckLOS();
	bool CheckLowHealth();
	bool CheckRange();
	float CurrentHealthPercentage();
	float CalculateHealthLength();
	AIState ais_CurrentState;

	//Enemy Actions
	void MoveLeft(float ElapsedTime);
	void MoveRight(float ElapsedTime);

	void Update(float ElapsedTime);
};