#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>
#include "Enemy.h"
#include "GeneralFunctions.h"

using namespace sf;

void Engine::Update(float ElapsedTime)
{
	map_Selected.ResetIndexes();
	map_Selected.LoadLocalCollisions(player);
	for (int count = 0; count < map_Selected.int_NumEnemies; count++)
	{
		map_Selected.LoadLocalEnemies(count, player, ene_Spawned[count]);
	}

	if (player.sta_Current.TookDamage == true)
	{
		hud.UpdateReports(INPUT, player.dr_Input);
	}

	// Player Updaters
	ProcessPlayer(ElapsedTime, player);
	DetectCollisionPlayer(player);
	player.UpdatePlayer(ElapsedTime, flo_AngleCursor);
	
	// Enemy Updaters
	for (int count = 0; count < map_Selected.int_MaxEnemyIndex; count++)
	{
		if (ene_Spawned[map_Selected.int_LoadedEnemies[count]].flo_FinalDuration > 0)
		{
			ProcessAI(ElapsedTime, ene_Spawned[map_Selected.int_LoadedEnemies[count]], player);
			DetectCollisionEnemy(ene_Spawned[map_Selected.int_LoadedEnemies[count]]);
			ene_Spawned[map_Selected.int_LoadedEnemies[count]].Update(ElapsedTime);
		}
	}
	
	// Camera Updaters
	UpdateCamera();
	hud.AttachCamera(vew_PlayerCamera);
	hud.UpdateHUD(player);
}

void Engine::DetectCollisionPlayer(Player &player)
{

	sf::Vector2f edge(0, 0);
	sf::Vector2f difference(0, 0);

	// Cycle through all surfaces
	for (int count = 0; count < map_Selected.int_MaxCollisionIndex; count++)
	{
		// Detect surface type and apply effects
		switch (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].pt_Type)
		{
		case PT_FLOOR: //Set player position to top of surface, zero y-velocity, stop falling and allow jumping.
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(player.GetSprite().getGlobalBounds()) && player.GetState().Jumping == false)
			{
				edge.x = player.GetPosition().x;
				edge.y = player.GetPosition().y + 33;

				difference.y = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().y) - edge.y;
				if (player.GetVelocity().y > difference.y)
				{
					player.vec_Velocity.y = difference.y + 1;
					player.sta_Current.Falling = false;
					player.sta_Current.CanJump = true;
				}
			}
			break;
		case PT_CEILING: //Set player position to bottom of surface
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(player.GetSprite().getGlobalBounds()))
			{
				edge.x = player.GetPosition().x;
				edge.y = player.GetPosition().y - 33;

				difference.y = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().y) - edge.y;
				if (player.GetVelocity().y < difference.y)
				{
					player.vec_Velocity.y = difference.y + 1;
				}
			}
			break;
		case PT_LEFT_WALL: //Set player position to right of surface
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(player.GetSprite().getGlobalBounds()) && (player.GetVelocity().y < 2 || player.GetVelocity().y > -2))
			{
				edge.x = player.GetPosition().x - 33;
				edge.y = player.GetPosition().y;

				difference.x = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().x) - edge.x;
				if (player.GetVelocity().x < difference.x)
				{
					player.vec_Velocity.x = difference.x + 1;
				}
			}
			break;
		case PT_RIGHT_WALL: //Set player position to left of surface
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(player.GetSprite().getGlobalBounds()) && (player.GetVelocity().y < 2 || player.GetVelocity().y > -2))
			{
				edge.x = player.GetPosition().x + 33;
				edge.y = player.GetPosition().y;

				difference.x = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().x) - edge.x;
				if (player.GetVelocity().x > difference.x)
				{
					player.vec_Velocity.x = difference.x + 1;
				}
			}
			break;
		}
	}

	// Cycle through all slopes
	for (int count = 0; count < map_Selected.int_NumSlop; count++)
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


void Engine::ProcessPlayer(float ElapsedTime, Player &player)
{
	if (player.sta_Current.MovingL == true)
	{
		player.vec_Velocity.x -= player.GetAttributes().MovementSpeed * ElapsedTime;
	}

	if (player.sta_Current.MovingR == true)
	{
		player.vec_Velocity.x += player.GetAttributes().MovementSpeed * ElapsedTime;
	}

	if (player.sta_Current.Jumping == true)
	{
		player.ProcessJump(ElapsedTime);
	}

	if (player.sta_Current.Rolling == true)
	{
		player.ProcessRoll(ElapsedTime);
	}

	if (player.sta_Current.Meleeing == true)
	{
		player.ProcessMelee(ElapsedTime);
	}

	if (player.sta_Current.Shooting == true)
	{
		player.ProcessRange(ElapsedTime);
	}
}

void Engine::ProcessAI(float ElapsedTime, EnemyObject &enemy, Player &player)
{
	switch (enemy.GetID())
	{
	case 1:
		GruntAI(ElapsedTime, enemy, player);
		break;
	case 2: 
		EliteAI(ElapsedTime, enemy, player);
		break;
	}
}

// Checks if player is colliding with any surface
void Engine::DetectCollisionEnemy(EnemyObject &enemy)
{
	sf::Vector2f edge(0, 0);
	sf::Vector2f difference(0, 0);

	// Cycle through all surfaces
	for (int count = 0; count < map_Selected.int_MaxCollisionIndex; count++)
	{
		// Detect surface type and apply effects
		switch (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].pt_Type)
		{
		case PT_FLOOR: //Set player position to top of surface, zero y-velocity, stop falling and allow jumping.
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(enemy.GetSprite().getGlobalBounds()) && enemy.GetState().Jumping == false)
			{
				edge.x = enemy.GetPosition().x;
				edge.y = enemy.GetPosition().y + 33;

				difference.y = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().y) - edge.y;
				if (enemy.GetVelocity().y > difference.y)
				{
					enemy.vec_Velocity.y = difference.y + 1;
					enemy.sta_Current.Falling = false;
					enemy.sta_Current.CanJump = true;
				}
			}
			break;
		case PT_CEILING: //Set player position to bottom of surface
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(enemy.GetSprite().getGlobalBounds()))
			{
				edge.x = enemy.GetPosition().x;
				edge.y = enemy.GetPosition().y - 33;

				difference.y = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().y) - edge.y;
				if (enemy.GetVelocity().y < difference.y)
				{
					enemy.vec_Velocity.y = difference.y + 1;
				}
			}
			break;
		case PT_LEFT_WALL: //Set player position to right of surface
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(enemy.GetSprite().getGlobalBounds()) && (enemy.GetVelocity().y < 2 || enemy.GetVelocity().y > -2))
			{
				edge.x = enemy.GetPosition().x - 33;
				edge.y = enemy.GetPosition().y;

				difference.x = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().x) - edge.x;
				if (enemy.GetVelocity().x < difference.x)
				{
					enemy.vec_Velocity.x = difference.x + 1;
				}
			}
			break;
		case PT_RIGHT_WALL: //Set player position to left of surface
			if (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getGlobalBounds().intersects
				(enemy.GetSprite().getGlobalBounds()) && (enemy.GetVelocity().y < 2 || enemy.GetVelocity().y > -2))
			{
				edge.x = enemy.GetPosition().x + 33;
				edge.y = enemy.GetPosition().y;

				difference.x = (map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea.getPosition().x) - edge.x;
				if (enemy.GetVelocity().x > difference.x)
				{
					enemy.vec_Velocity.x = difference.x + 1;
				}
			}
			break;
		}
	}

	// Cycle through all slopes
	for (int count = 0; count < map_Selected.int_NumSlop; count++)
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
			|| map_Selected.slo_SlopeData[count].col_RightCollision.rs_CollisionArea.getGlobalBounds().intersects(enemy.GetSprite().getGlobalBounds()))
			&& enemy.GetState().Jumping == false)
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
					enemy.sta_Current.CanJump = true;
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
					enemy.sta_Current.CanJump = true;
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
					&& enemy.GetPosition().y < startPoint.y + difference + 34)
				{
					enemy.vec_Position.y = startPoint.y + difference + 34;
					enemy.vec_Velocity.y = 0;
				}
			}
		}
	}
}