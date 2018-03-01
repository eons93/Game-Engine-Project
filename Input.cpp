#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>

void Engine::input()
{
	
	switch (event.type)
	{
	case sf::Event::EventType::JoystickButtonPressed:
		std::cout << event.joystickButton.joystickId << std::endl;
	}
	
	// Resets Position/Velocity Data
	if (Keyboard::isKeyPressed(Keyboard::H))
	{
		player.resetMinMax(player.position, player.velocity);
	}

	// Handle the player quitting
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	// Handle the player moving Left/Right
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		player.moveLeft();
	}
	else
	{
		player.stopLeft();
	}
	
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		player.moveRight();
	}
	else
	{
		player.stopRight();
	}

	// Handle Player Duck and Roll
	if (Keyboard::isKeyPressed(Keyboard::S) && player.jumping == false)
	{
		player.engageDuck();
	}
	else
	{
		player.disengageDuck();
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && (player.ducking == true && player.rolling == false))
	{
		player.engageLeftRoll();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && (player.ducking == true && player.rolling == false))
	{
		player.engageRightRoll();
	}

	
	// Handle Player Jumping
	if (Keyboard::isKeyPressed(Keyboard::W) && player.canJump == true)
	{
		player.engageJump();
	}
}