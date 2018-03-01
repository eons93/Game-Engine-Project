#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"


using namespace sf;

class Player
{

private:

	// Player's Stats
	float moveSpeed;
	float angle;
	float jumpSpeed;

	float jumpHeight;
	int jumpDuration;
	int jumpCounter;
	

	bool rollFaceHolder;
	int rollDelay;
	int rollDuration;
	int rollCounter;
	float rollMovement;
	
	// Manages what to draw
	sf::IntRect selection;
	sf::Sprite current;
	sf::Texture texture;
	Animation currentAnimatation;

	void reverseSprite();

	//computes what the player class needs to do
	void manager();
	
public:
	Player();

	// Manages what to draw. 
	void loadAnimations();
	void attachAnimation(Animation _new);
	void stateDetector();
	Sprite getSprite();
	sf::Vector2f getPosition();
	Animation currentAnimation();
	CollisionObject hitBox;


	// Variables to Detect Player State
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

	// Manages States
	void copyState(ComplexState holder);
	bool compareState();
	ComplexState stateHolder;
	bool facingHolder;

	// Player Animations
	Animation idle;
	Animation run;
	Animation shoot;
	Animation melee;
	Animation airShoot;
	Animation airMelee;
	Animation jump;
	Animation fall;
	Animation roll;
	Animation duck;
	Animation block;

	bool canJump;

	// Misc Stats
	sf::Vector2f position;
	sf::Vector2f velocity;
	void spawn(Map map);
	float maxX;
	float maxY;
	float minX;
	float minY;
	float minVelX;
	float maxVelX;
	float minVelY;
	float maxVelY;
	void checkMinMax(sf::Vector2f position, sf::Vector2f velocity);
	void resetMinMax(sf::Vector2f position, sf::Vector2f velocity);


	//Player Actions
	void moveRight();
	void moveLeft();
	void stopRight();
	void stopLeft();

	void engageJump();
	void processJump();
	void disengageJump();

	void engageDuck();
	void disengageDuck();

	void engageLeftRoll();
	void engageRightRoll();
	void processRoll();
	void DisengageRoll();

	//Updater
	void updateStage1();
	void updateStage2();

	

};