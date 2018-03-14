#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>
#include "Enemy.h"
#include "GeneralFunctions.h"

using namespace sf;

void Engine::Update(float ElapsedTime)
{
	// Player Updaters
	player.UpdatePhase1(ElapsedTime);
	DetectCollisionPlayer(player);
	player.UpdatePhase2(ElapsedTime);

	// Enemy Updaters
	for (int count = 0; count < map_Selected.int_NumEnemies; count++)
	{
		ProcessAI(ElapsedTime, ene_Spawned[count]);
		DetectCollisionEnemy(ene_Spawned[count]);
		ene_Spawned[count].Update(ElapsedTime);
	}
	
	// Camera Updaters
	UpdateCamera();
	hud.AttachCamera(vew_PlayerCamera);
	hud.UpdateHUD(player);
}

// Checks if player is colliding with any surface
void Engine::DetectCollisionPlayer(Player &player)
{
	// Cycle through all surfaces
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		// Detect surface type and apply effects
		switch (map_Selected.col_CollisionData[count].pt_Type)
		{
		case PT_FLOOR: //Set player position to top of surface, zero y-velocity, stop falling and allow jumping.
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
				&& player.GetState().Jumping == false)
			{
				player.vec_Position.y = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().y - 32;
				player.vec_Velocity.y = 0;
				player.sta_Current.Falling = false;
				player.sta_Current.CanJump = true;
			}
			break;
		case PT_CEILING: //Set player position to bottom of surface
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds()))
			{
				player.vec_Position.y = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().y + 34;
				player.vec_Velocity.y = 0;
			}
			break;
		case PT_LEFT_WALL: //Set player position to right of surface
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
				&& (player.GetVelocity().y < 2 || player.GetVelocity().y > -2))
			{
				player.vec_Position.x = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().x + 34;
			}
			break;
		case PT_RIGHT_WALL: //Set player position to left of surface
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
				&& (player.GetVelocity().y < 2 || player.GetVelocity().y > -2))
			{
				player.vec_Position.x = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().x - 34;
			}
			break;
		}
	}

	// Cycle through all platforms
	for (int count = 0; count < MAXPLATFORMS; count++)
	{
		// If player is colliding with floor surface of platform and is not jumping
		//		--Set Position to proper
		//		--Set velocity to 0
		//		--Allow player to jump and not be in falling state
		if (map_Selected.pla_PlatformData[count].col_TopCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
			&& player.GetState().Jumping == false)
		{
			player.vec_Position.y = map_Selected.pla_PlatformData[count].col_TopCollision.rs_CollisionArea.getPosition().y - 32;
			player.vec_Velocity.y = 0;
			player.sta_Current.Falling = false;
			player.sta_Current.CanJump = true;
		}
		// If player is colliding with ceiling surface
		//		--Set Position to proper
		//		--Set Velocity to 0
		if (map_Selected.pla_PlatformData[count].col_BottomCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds()))
		{
			player.vec_Position.y = map_Selected.pla_PlatformData[count].col_BottomCollision.rs_CollisionArea.getPosition().y + 34;
			player.vec_Velocity.y = 0;
		}
		// If player is colliding with left surface
		//		--Set Position to proper
		if (map_Selected.pla_PlatformData[count].col_LeftCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
			&& (player.GetVelocity().y < 2 || player.GetVelocity().y > -2))
		{
			player.vec_Position.x = map_Selected.pla_PlatformData[count].col_LeftCollision.rs_CollisionArea.getPosition().x + 34;
		}
		// If player is colliding with right surface
		//		--Set Position to proper
		if (map_Selected.pla_PlatformData[count].col_RightCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
			&& (player.GetVelocity().y < 2 || player.GetVelocity().y > -2))
		{
			player.vec_Position.x = map_Selected.pla_PlatformData[count].col_RightCollision.rs_CollisionArea.getPosition().x - 34;
		}
	}

	// Cycle through all slopes
	for (int count = 0; count < MAXSLOPES; count++)
	{
		// Placeholders
		sf::Vector2f startPoint;
		sf::Vector2f playerPoint;
		float difference;
		float angle = map_Selected.slo_SlopeData[count].flo_Slope;

		// Assign values for the focal point of slope detection of player
		startPoint.x = map_Selected.slo_SlopeData[count].col_TopCollision.rs_CollisionArea.getGlobalBounds().left + 8;
		startPoint.y = map_Selected.slo_SlopeData[count].col_BottomCollision.rs_CollisionArea.getGlobalBounds().top - 8;

		// If the player is colliding with slope and is not jumping
		if ((map_Selected.slo_SlopeData[count].col_TopCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
			|| map_Selected.slo_SlopeData[count].col_BottomCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
			|| map_Selected.slo_SlopeData[count].col_LeftCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds())
			|| map_Selected.slo_SlopeData[count].col_RightCollision.rs_CollisionArea.getGlobalBounds().intersects(player.GetSprite().getGlobalBounds()))
			&& player.GetState().Jumping == false)
		{
			// Right Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == false &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.GetPosition().x + 34;
				playerPoint.y = player.GetPosition().y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& player.GetPosition().y > startPoint.y - difference - 34)
				{
					player.vec_Position.y = startPoint.y - (difference / angle) - 34;
					player.vec_Velocity.y = 0;
					player.sta_Current.Falling = false;
					player.sta_Current.CanJump = true;
				}
			}
			//Left Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == false &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.GetPosition().x - 34;
				playerPoint.y = player.GetPosition().y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& player.GetPosition().y > startPoint.y + difference - 96)
				{
					player.vec_Position.y = startPoint.y + (difference / angle) - 96;
					player.vec_Velocity.y = 0;
					player.sta_Current.Falling = false;
					player.sta_Current.CanJump = true;
				}
			}
			//Right Inverted Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == true &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.GetPosition().x + 34;
				playerPoint.y = player.GetPosition().y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& player.GetPosition().y < startPoint.y - difference + 96)
				{
					player.vec_Position.y = startPoint.y - difference + 96;
					player.vec_Velocity.y = 0;
				}
			}
			//Left Inverted Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == true &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.GetPosition().x - 34;
				playerPoint.y = player.GetPosition().y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& player.GetPosition().y < startPoint.y + difference + 34)
				{
					player.vec_Position.y = startPoint.y + difference + 34;
					player.vec_Velocity.y = 0;
				}
			}
		}
	}
}

void Engine::ProcessAI(float ElapsedTime, EnemyObject &enemy)
{
	switch (enemy.GetID())
	{
	case 1:
		GruntAI(ElapsedTime, enemy);
		break;
	case 2: 
		EliteAI(ElapsedTime, enemy);
		break;
	}
}

// Checks if player is colliding with any surface
void Engine::DetectCollisionEnemy(EnemyObject &enemy)
{
	// Cycle through all surfaces
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		// Detect surface type and apply effects
		switch (map_Selected.col_CollisionData[count].pt_Type)
		{
		case PT_FLOOR: //Set player position to top of surface, zero y-velocity, stop falling and allow jumping.
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds()))
				//&& enemy.jumping == false)
			{
				enemy.vec_Position.y = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().y - 32;
				enemy.vec_Velocity.y = 0;
				enemy.sta_Current.Falling = false;
				//enemy.canJump = true;
			}
			break;
		case PT_CEILING: //Set player position to bottom of surface
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds()))
			{
				enemy.vec_Position.y = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().y + 34;
				enemy.vec_Velocity.y = 0;
			}
			break;
		case PT_LEFT_WALL: //Set player position to right of surface
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())
				&& (enemy.GetVelocity().y < 2 || enemy.GetVelocity().y > -2))
			{
				enemy.vec_Position.x = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().x + 34;
			}
			break;
		case PT_RIGHT_WALL: //Set player position to left of surface
			if (map_Selected.col_CollisionData[count].rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())
				&& (enemy.GetVelocity().y < 2 || enemy.GetVelocity().y > -2))
			{
				enemy.vec_Position.x = map_Selected.col_CollisionData[count].rs_CollisionArea.getPosition().x - 34;
			}
			break;
		}
	}

	// Cycle through all platforms
	for (int count = 0; count < MAXPLATFORMS; count++)
	{
		// If player is colliding with floor surface of platform and is not jumping
		//		--Set Position to proper
		//		--Set velocity to 0
		//		--Allow player to jump and not be in falling state
		if (map_Selected.pla_PlatformData[count].col_TopCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds()))
			//&& player.jumping == false)
		{
			enemy.vec_Position.y = map_Selected.pla_PlatformData[count].col_TopCollision.rs_CollisionArea.getPosition().y - 32;
			enemy.vec_Velocity.y = 0;
			enemy.sta_Current.Falling = false;
			//enemy.canJump = true;
		}
		// If player is colliding with ceiling surface
		//		--Set Position to proper
		//		--Set Velocity to 0
		if (map_Selected.pla_PlatformData[count].col_BottomCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds()))
		{
			enemy.vec_Position.y = map_Selected.pla_PlatformData[count].col_BottomCollision.rs_CollisionArea.getPosition().y + 34;
			enemy.vec_Velocity.y = 0;
		}
		// If player is colliding with left surface
		//		--Set Position to proper
		if (map_Selected.pla_PlatformData[count].col_LeftCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())
			&& (enemy.GetVelocity().y < 2 || enemy.GetVelocity().y > -2))
		{
			enemy.vec_Position.x = map_Selected.pla_PlatformData[count].col_LeftCollision.rs_CollisionArea.getPosition().x + 34;
		}
		// If player is colliding with right surface
		//		--Set Position to proper
		if (map_Selected.pla_PlatformData[count].col_RightCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())
			&& (enemy.GetVelocity().y < 2 || enemy.GetVelocity().y > -2))
		{
			enemy.vec_Position.x = map_Selected.pla_PlatformData[count].col_RightCollision.rs_CollisionArea.getPosition().x - 34;
		}
	}

	// Cycle through all slopes
	for (int count = 0; count < MAXSLOPES; count++)
	{
		// Placeholders
		sf::Vector2f startPoint;
		sf::Vector2f playerPoint;
		float difference;
		float angle = map_Selected.slo_SlopeData[count].flo_Slope;

		// Assign values for the focal point of slope detection of player
		startPoint.x = map_Selected.slo_SlopeData[count].col_TopCollision.rs_CollisionArea.getGlobalBounds().left + 8;
		startPoint.y = map_Selected.slo_SlopeData[count].col_BottomCollision.rs_CollisionArea.getGlobalBounds().top - 8;

		// If the player is colliding with slope and is not jumping
		if ((map_Selected.slo_SlopeData[count].col_TopCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())
			|| map_Selected.slo_SlopeData[count].col_BottomCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())
			|| map_Selected.slo_SlopeData[count].col_LeftCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())
			|| map_Selected.slo_SlopeData[count].col_RightCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds())))
			//&& player.jumping == false)
		{
			// Right Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == false &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.GetPosition().x + 34;
				playerPoint.y = enemy.GetPosition().y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& enemy.GetPosition().y > startPoint.y - difference - 34)
				{
					enemy.vec_Position.y = startPoint.y - (difference / angle) - 34;
					enemy.vec_Velocity.y = 0;
					enemy.sta_Current.Falling = false;
					//enemy.canJump = true;
				}
			}
			//Left Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == false &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.GetPosition().x - 34;
				playerPoint.y = enemy.GetPosition().y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& enemy.GetPosition().y > startPoint.y + difference - 96)
				{
					enemy.vec_Position.y = startPoint.y + (difference / angle) - 96;
					enemy.vec_Velocity.y = 0;
					enemy.sta_Current.Falling = false;
					//enemy.canJump = true;
				}
			}
			//Right Inverted Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == true &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.GetPosition().x + 34;
				playerPoint.y = enemy.GetPosition().y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& enemy.GetPosition().y < startPoint.y - difference + 96)
				{
					enemy.vec_Position.y = startPoint.y - difference + 96;
					enemy.vec_Velocity.y = 0;
				}
			}
			//Left Inverted Slope
			if (map_Selected.slo_SlopeData[count].bol_Inverted == true &&
				map_Selected.slo_SlopeData[count].bol_LeftorRight == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.GetPosition().x - 34;
				playerPoint.y = enemy.GetPosition().y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& enemy.vec_Position.y < startPoint.y + difference + 34)
				{
					enemy.vec_Position.y = startPoint.y + difference + 34;
					enemy.vec_Velocity.y = 0;
				}
			}
		}
	}
}