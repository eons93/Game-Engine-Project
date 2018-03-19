#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include <cmath>
#include <iostream>

void Engine::Input()
{
	vec_CursorPosition.x = sf::Mouse::getPosition(m_Window).x - (Resolution.x / 2);
	vec_CursorPosition.y = sf::Mouse::getPosition(m_Window).y - (Resolution.y / 2);
	flo_AngleCursor = (atan2(vec_CursorPosition.x, vec_CursorPosition.y) * 180 / PI) + 180;

	//std::cout << "Change: " << vec_CursorPosition.x << " : " << vec_CursorPosition.y << std::endl;
	std::cout << "Angle:  " << flo_AngleCursor << std::endl;

	// Resets Position/Velocity Data
	if (Keyboard::isKeyPressed(Keyboard::H))
	{
		player.ResetMinMax(player.vec_Position, player.vec_Velocity);
	}

	// Handle the player quitting
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}


	// Handle the player moving Left/Right
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		player.MoveLeft();
	}
	else
	{
		player.StopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		player.MoveRight();
	}
	else
	{
		player.StopRight();
	}

	// Handle Player Duck and Roll
	if (Keyboard::isKeyPressed(Keyboard::S) && player.GetState().Jumping == false)
	{
		player.EngageDuck();
	}
	else
	{
		player.DisengageDuck();
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && (player.GetState().Ducking == true && player.GetState().Rolling == false))
	{
		player.EngageLeftRoll();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && (player.GetState().Ducking == true && player.GetState().Rolling == false))
	{
		player.EngageRightRoll();
	}

	// Handle Player Jumping
	if (Keyboard::isKeyPressed(Keyboard::W) && player.GetState().CanJump == true)
	{
		player.EngageJump();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2))
	{
		std::cout << "pooper scooper are just largend" << std::endl;
		player.EngageRange();
	}

	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		player.EngageMelee();
	}

	

}