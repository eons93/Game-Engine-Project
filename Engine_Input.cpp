#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include "GeneralFunctions.h"
#include <cmath>
#include <iostream>

void Engine::Input()
{
	sf::Event event;

	while (m_Window.pollEvent(event))
	{
		// Updates Cursor Position and Angle
		vec_CursorPosition.x = sf::Mouse::getPosition(m_Window).x - (Resolution.x / 2);
		vec_CursorPosition.y = sf::Mouse::getPosition(m_Window).y - (Resolution.y / 2);
		flo_AngleCursor = (atan2(vec_CursorPosition.x, vec_CursorPosition.y) * 180 / PI) + 180;

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}

		//-------------HUD INPUT-------------------

		// Resets Position/Velocity Data
		if (Keyboard::isKeyPressed(Keyboard::H))
		{
			hud.ResetMinMax(player.vec_Position, player.vec_Velocity);
		}

		if (Keyboard::isKeyPressed(Keyboard::Num0))
		{
			hud.ht_CurrentMode = RELEASE;
		}

		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			hud.ht_CurrentMode = MOVEMENT;
		}

		if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			hud.ht_CurrentMode = COMBAT;
		}

		
		//-----------PLAYER INPUT-----------------

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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) 
			&& (player.sta_Current.Shooting == false && player.sta_Current.Meleeing == false))
		{
			int num = 0;

			for (int count = 0; count < map_Selected.int_NumEnemies; count++)
			{
				if (ene_Spawned[count].flo_FinalDuration > 0)
				{
					num++;
					player.EngageRange(flo_AngleCursor, ene_Spawned[count]);
					hud.UpdateReports(player.GetDamageReport());
				}
			}
			if (num == 0)
			{
				EnemyObject blank;
				player.EngageRange(flo_AngleCursor, blank);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::F)
			&& (player.sta_Current.Shooting == false && player.sta_Current.Meleeing == false))
		{
			int num = 0;

			for (int count = 0; count < map_Selected.int_NumEnemies; count++)
			{
				if (ene_Spawned[count].flo_FinalDuration > 0)
				{
					num++;
					player.EngageMelee(flo_AngleCursor, ene_Spawned[count]);
					hud.UpdateReports(player.GetDamageReport());
				}
			}
			if (num == 0)
			{
				EnemyObject blank;
				player.EngageMelee(flo_AngleCursor, blank);
			}
		}
	}
}