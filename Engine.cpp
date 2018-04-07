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
	std::cout << "Platform Object Size:  " << sizeof(PlatformObject) << std::endl;
	std::cout << "Animation Size:        " << sizeof(Animation) << std::endl;
	std::cout << "Player Size:           " << sizeof(Player) << std::endl;

	ene_Spawned.resize(200);

	// Get the screen resolution and create an SFML window and View
	Resolution.x = VideoMode::getDesktopMode().width;
	Resolution.y = VideoMode::getDesktopMode().height;
	
	frameCounter = 0;

	m_Window.create(VideoMode(Resolution.x, Resolution.y),
		"Game Engine",
		Style::Fullscreen);

	sf::Vector2f enemyPos(200, 20);
	sf::Vector2f playerPos(400, 20);

	sf::Vector2f TrueA(300, 0);
	sf::Vector2f TrueB(300, 40);

	LinearFunc enemyPlayer = LinearOf(enemyPos, playerPos);
	LinearFunc wall = LinearOf(TrueA, TrueB);
	sf::Vector2f intersect = IntersectOf(enemyPlayer, wall);


	//std::cout << UNDEFINED << std::endl;
	//std::cout << UNDEFINEDNEG << std::endl;
	std::cout << "Enemy/Player Line: slope of " << enemyPlayer.Slope << ", intersect of " << enemyPlayer.Intercept << std::endl;
	std::cout << "   Collision Line: slope of " << wall.Slope << ", intersect of " << wall.Intercept << std::endl;
	std::cout << "These Lines INtersect at (" << intersect.x << ", " << intersect.y << ")" << std::endl;

	// Load Level
	LoadAnimations();
	LoadMaps();
	LoadEnemies();
	AttachMap(map_Arena1);
	AttachTexture();
	AttachMapEnemies();

	ene_Spawned.resize(map_Selected.int_NumEnemies);

	rs_Background.setSize(sf::Vector2f(Resolution.x, Resolution.y));
	rs_Background.setOrigin(sf::Vector2f(Resolution.x / 2, Resolution.y / 2));
	rs_Background.setPosition(sf::Vector2f(player.GetPosition().x, player.GetPosition().y));

	
	// Load Player
	player.Spawn(map_Selected);
	vew_PlayerCamera.setCenter(player.GetPosition());
	vew_PlayerCamera.setSize(Resolution.x * 0.625, Resolution.y * 0.625);
	hud.AttachCamera(vew_PlayerCamera);
}

void Engine::start()
{
	// Timing
	sf::Clock clock;
	
	while (m_Window.isOpen())
	{
		

		// Restart the clock and save the elapsed time into dt
		Time dt = clock.restart();

		// Make a fraction from the delta time
		float dtAsSeconds = dt.asSeconds();
		
		Input();
		Update(dtAsSeconds);
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
		std::cout << frameCounter << std::endl;
		frameCounter = 0;
		secondsClock.restart();
	}
}

void Engine::UpdateCamera()
{
	rs_Background.setPosition(sf::Vector2f(player.GetPosition().x, player.GetPosition().y));

	m_Window.setView(vew_PlayerCamera);
	vew_PlayerCamera.setCenter(sf::Vector2f(player.GetPosition().x, player.GetPosition().y));
}

void Engine::AttachMapEnemies()
{
	for (int count = 0; count < map_Selected.int_NumEnemies; count++)
	{
		switch (map_Selected.et_EnemyData[count])
		{
		case ET_ELITE:
			ene_Spawned[count] = ene_Elite;
			break;
		case ET_GRUNT:
			ene_Spawned[count] = ene_Grunt;
			break;
		}
		ene_Spawned[count].flo_CurrentHealth = ene_Spawned[count].att_Stats.Health;
		ene_Spawned[count].flo_CurrentShields = ene_Spawned[count].att_Stats.Shield;
		ene_Spawned[count].sta_Current.CurrentState = CS_GROUND_FACE;
		ene_Spawned[count].Spawn(count, map_Selected);
	}
}