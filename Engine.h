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
	void Update();
	void Draw();

	// Update Functions
	void UpdateCamera();
	void DetectCollisionPlayer(Player &Lplayer);
	void DetectCollisionEnemy(EnemyObject &enemy);

	//Maps
	Map map_TestChamber;

	//Animations
	Animation ani_EliteIdle;
	Animation ani_EliteFall;
	Animation ani_EliteRun;
	Animation ani_GruntIdle;
	Animation ani_GruntFall;
	Animation ani_GruntRun;

	//Enemies
	EnemyObject ene_Elite;
	EnemyObject ene_Grunt;


public:
	// The Engine constructor
	Engine();

	// start will call all the private functions
	void start();

};
