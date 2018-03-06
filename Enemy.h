#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include <string>


class Map;

using namespace sf;

class EnemyObject
{
private:
	
public:
	EnemyObject();

	std::string str_Name;
	sf::Font fon_Enemy;
	sf::Text txt_Name;

	sf::Vector2f vec_Position;
	sf::Vector2f vec_Velocity;

	sf::Sprite GetSprite();
	void Spawn(int ID, Map map);

	// Regulate what to Draw
	Animation CurrentAnimationFunc();
	void ReverseSprite();
	sf::Sprite spr_CurrentSprite;
	Animation ani_Current_State_Animation;
	Animation ani_Idle;
	Animation ani_Run;
	Animation ani_Fall;
	
	// Regulate State
	void StateDetector();
	void CopyState(ComplexState holder);
	bool CompareState();
	ComplexState cs_StateHolder;
	bool bol_FacingHolder;

	// Factors of State
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

	void Update();
};