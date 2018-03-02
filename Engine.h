#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Level.h"
#include "Map.h"
#include "Enumerations.h"
#include "HUD.h"

using namespace sf;

class Engine
{
private:

	// A regular RenderWindow
	RenderWindow m_Window;
	Vector2f resolution;

	//Load Map
	Map map;
	sf::Event event;

	// Load Level
	Level level;

	// Load Player
	Player player;
	HUD hud;
	sf::View playerCamera;
	sf::Vector2f playerLocation;

	// Load FPS Limiter Parts
	void limiterFPS();
	sf::Clock frameClock;
	sf::Clock secondsClock;
	sf::Time timeperFrame;
	sf::Time secondsChecker;

	float limiter;
	sf::Int32 frameCounter;
	bool controlConnect;

	// Private functions for internal use only
	void input();
	void update();
	void draw();

	void updateCamera();

public:
	// The Engine constructor
	Engine();

	// start will call all the private functions
	void start();

};
