#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include "Level.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include <string.h>

Engine::Engine()
{
	// Inform class Sizes
	std::cout << "Player Size:           " << sizeof(Player) << std::endl;
	std::cout << "Map Size:              " << sizeof(Map) << std::endl;
	std::cout << "Level Size:            " << sizeof(Level) << std::endl;
	std::cout << "Engine Size:           " << sizeof(Engine) << std::endl;
	std::cout << "Aniamtion Size:        " << sizeof(Animation) << std::endl;
	std::cout << "Collision Object Size: " << sizeof(CollisionObject) << std::endl;
	std::cout << "Slope Object Size:     " << sizeof(SlopeObject) << std::endl;
	std::cout << "Platform Ibject Size:  " << sizeof(PlatformObject) << std::endl;
	std::cout << "HUD Size:              " << sizeof(HUD) << std::endl;

	// Get the screen resolution and create an SFML window and View
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	
	frameCounter = 0;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Game Engine",
		Style::Fullscreen);

	// Load Level
	level.loadMaps();
	level.attachMap(level.playground);
	level.attachTexture();
	level.background.setSize(sf::Vector2f(resolution.x, resolution.y));
	level.background.setOrigin(sf::Vector2f(resolution.x / 2, resolution.y / 2));
	level.background.setPosition(sf::Vector2f(player.position.x, player.position.y));

	// Load Player
	player.spawn(level.selectedMap);
	player.loadAnimations();
	player.attachAnimation(player.idle);

	

	playerCamera.setCenter(player.position);
	playerCamera.setSize(resolution.x * 0.625, resolution.y * 0.625);
	hud.attachCamera(playerCamera);

	
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
		
		input();
		update();
		draw();
		limiterFPS();
	}
}

void Engine::limiterFPS()
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
		//std::cout << frameCounter << std::endl;
		frameCounter = 0;
		secondsClock.restart();
	}
}

void Engine::updateCamera()
{

	level.background.setPosition(sf::Vector2f(player.position.x, player.position.y));

	m_Window.setView(playerCamera);
	playerCamera.setCenter(sf::Vector2f(player.position.x, player.position.y));
	

}