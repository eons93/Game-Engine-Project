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

	std::string name;

	sf::Vector2f position;
	sf::Vector2f velocity;

	void spawn(int ID, Map map);

	Animation currentAnimationFunc();
	void reverseSprite();
	sf::Sprite currentSprite;
	Animation currentState_Animation;
	Animation idle;
	Animation run;
	Animation fall;
	
	void stateDetector();
	void copyState(ComplexState holder);
	bool compareState();
	ComplexState stateHolder;
	bool facingHolder;

	bool facing;

	bool jumping;
	bool ducking;
	bool rolling;
	bool blocking;
	bool falling;
	bool shooting;
	bool meleeing;
	bool movingL;
	bool movingR;
	ComplexState currentState;

	void Update();

	sf::Sprite getSprite();
};