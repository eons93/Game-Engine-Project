#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include <string.h>
#include "Enemy.h"

Engine::Engine()
{
	// Inform class Sizes
	std::cout << "Engine Size:           " << sizeof(Engine) << std::endl;
	std::cout << "HUD Size:              " << sizeof(HUD) << std::endl;
	std::cout << "Map Size:              " << sizeof(Map) << std::endl;
	std::cout << "Collision Object Size: " << sizeof(CollisionObject) << std::endl;
	std::cout << "Slope Object Size:     " << sizeof(SlopeObject) << std::endl;
	std::cout << "Platform Ibject Size:  " << sizeof(PlatformObject) << std::endl;
	std::cout << "Aniamtion Size:        " << sizeof(Animation) << std::endl;
	std::cout << "Player Size:           " << sizeof(Player) << std::endl;

	ene_Spawned.resize(MAXENEMIES);

	// Get the screen resolution and create an SFML window and View
	Resolution.x = VideoMode::getDesktopMode().width;
	Resolution.y = VideoMode::getDesktopMode().height;
	
	frameCounter = 0;

	m_Window.create(VideoMode(Resolution.x, Resolution.y),
		"Game Engine",
		Style::Fullscreen);

	// Load Level
	LoadAnimations();
	LoadMaps();
	LoadEnemies();
	AttachMap(map_TestChamber);
	AttachTexture();
	AttachMapEnemies();
	rs_Background.setSize(sf::Vector2f(Resolution.x, Resolution.y));
	rs_Background.setOrigin(sf::Vector2f(Resolution.x / 2, Resolution.y / 2));
	rs_Background.setPosition(sf::Vector2f(player.vec_Position.x, player.vec_Position.y));

	
	
	// Load Player
	player.Spawn(map_Selected);
	player.LoadAnimations();
	
	vew_PlayerCamera.setCenter(player.vec_Position);
	vew_PlayerCamera.setSize(Resolution.x * 0.625, Resolution.y * 0.625);
	hud.AttachCamera(vew_PlayerCamera);
}

void Engine::start()
{
	// Timing
	//Clock clock;
	
	while (m_Window.isOpen())
	{
		// Restart the clock and save the elapsed time into dt
		//Time dt = clock.restart();

		// Make a fraction from the delta time
		//float dtAsSeconds = dt.asSeconds();
		
		Input();
		Update();
		Draw();
		LimiterFPS();
	}
}

void Engine::AttachMap(Map map)
{
	// Attach input map to be the selected map
	map_Selected = map;
}

void Engine::AttachTexture()
{
	rs_Background.setTexture(&map_Selected.txu_BackgroundImage);
	spr_LevelStructure.setTexture(map_Selected.txu_LevelImage);
}


void Engine::LimiterFPS()
{
	
retry:

	timeperFrame = frameClock.getElapsedTime();
	secondsChecker = secondsClock.getElapsedTime();
	limiter = 17.667;

	while (timeperFrame.asMilliseconds() < limiter)
	{
		goto retry;
	}
	frameCounter++;
	frameClock.restart();
	if (secondsChecker.asMilliseconds() >= 1000)
	{
		frameCounter = 0;
		secondsClock.restart();
	}
}

void Engine::UpdateCamera()
{
	rs_Background.setPosition(sf::Vector2f(player.vec_Position.x, player.vec_Position.y));

	m_Window.setView(vew_PlayerCamera);
	vew_PlayerCamera.setCenter(sf::Vector2f(player.vec_Position.x, player.vec_Position.y));
}

void Engine::AttachMapEnemies()
{
	for (int count = 0; count < MAXENEMIES; count++)
	{
		switch (map_Selected.et_EnemyData[count])
		{
		case ET_GRUNT:
			ene_Spawned[count] = ene_Grunt;
			break;
		}
		
		ene_Spawned[count].Spawn(count, map_Selected);
	}
}