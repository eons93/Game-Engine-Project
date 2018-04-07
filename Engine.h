#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Enumerations.h"
#include "HUD.h"
#include "Enemy.h"

using namespace sf;

class Engine
{
private:

	// A regular RenderWindow
	RenderWindow m_Window;
	Vector2f Resolution;

	// Holders
	std::vector<EnemyObject> ene_Spawned;
	Map map_Selected;
	sf::RectangleShape rs_Background;
	sf::Sprite spr_LevelStructure;

	//Loaders
	void LoadAnimations();
	void LoadMaps();
	void LoadEnemies();

	//Attachers
	void AttachMapEnemies();
	void AttachMap(Map map);
	void AttachTexture();

	// Load Player
	Player player;
	HUD hud;
	sf::Vector2f vec_CursorPosition;
	float flo_AngleCursor;
	sf::View vew_PlayerCamera;
	sf::Vector2f vec_PlayerLocation;

	// Load FPS Limiter Parts
	void LimiterFPS();
	sf::Clock frameClock;
	sf::Clock secondsClock;
	sf::Time timeperFrame;
	sf::Time secondsChecker;

	float limiter;
	sf::Int32 frameCounter;
	bool controlConnect;

	// Private functions for internal use only
	void Input();
	void Update(float ElapsedTime);
	void Draw();

	// Update Functions
	void UpdateCamera();
	void ProcessPlayer(float ElapsedTime, Player &player);
	void ProcessAI(float ElapsedTime, EnemyObject &enemy, Player &player);
	void DetectCollisionPlayer(Player &player);
	void DetectCollisionEnemy(EnemyObject &enemy);

	//Maps
	Map map_TestChamber;
	Map map_Arena1;

	//Animations
	Animation ani_EliteIdle;
	Animation ani_EliteDeath;
	Animation ani_EliteFall;
	Animation ani_EliteJump;
	Animation ani_EliteMelee;
	Animation ani_EliteRun;
	Animation ani_EliteBlock;
	Animation ani_EliteDuck;
	Animation ani_EliteRoll;
	sf::Texture txu_EliteFiring;
	sf::Texture txu_EliteAiming;
	sf::Texture txu_EliteNoShow;

	Animation ani_GruntIdle;
	Animation ani_GruntDeath;
	Animation ani_GruntFall;
	Animation ani_GruntJump;
	Animation ani_GruntMelee;
	Animation ani_GruntRun;
	Animation ani_GruntBlock;
	Animation ani_GruntDuck;
	Animation ani_GruntRoll;
	sf::Texture txu_GruntFiring;
	sf::Texture txu_GruntAiming;
	sf::Texture txu_GruntNoShow;

	//Enemies
	EnemyObject ene_Elite;
	EnemyObject ene_Grunt;

	//AI Components
	void Patrol(float ElapsedTime, EnemyObject &enemy, sf::Vector2f point1, sf::Vector2f point2);
	void Flee(float ElapsedTime, EnemyObject &enemy, float playerAngle);
	void Chase(float ElapsedTime, EnemyObject &enemy, float playerAngle);
	void AttackPlayer(float ElapsedTime, EnemyObject &enemy, Attack attack, Player &player);

	bool CheckWalls(EnemyObject enemy, Player player);
	bool DetectObstruction(EnemyObject enemy, Player player, LinearFunc enemy_Player, CollisionObject barrier);

	//Enemy AI's
	void GruntAI(float ElapsedTime, EnemyObject &enemy, Player player);
	void EliteAI(float ElapsedTime, EnemyObject &enemy, Player &player);
	

public:
	// The Engine constructor
	Engine();

	// start will call all the private functions
	void start();

};
