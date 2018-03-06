#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>

void Engine::Input()
{
	
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
		if (Keyboard::isKeyPressed(Keyboard::S) && player.bol_Jumping == false)
		{
			player.EngageDuck();
		}
		else
		{
			player.DisengageDuck();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && (player.bol_Ducking == true && player.bol_Rolling == false))
		{
			player.EngageLeftRoll();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && (player.bol_Ducking == true && player.bol_Rolling == false))
		{
			player.EngageRightRoll();
		}


		// Handle Player Jumping
		if (Keyboard::isKeyPressed(Keyboard::W) && player.bol_CanJump == true)
		{
			player.EngageJump();
		}
		
}