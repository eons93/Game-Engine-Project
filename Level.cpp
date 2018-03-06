#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "Engine.h"
#include "Enemy.h"
#include "GeneralFunctions.h"

Level::Level()
{
	
}
/*
// Applies map's textures 
void Level::attachTexture()
{
	background.setTexture(&selectedMap.txu_BackgroundImage);
	levelStructure.setTexture(selectedMap.txu_LevelImage);
}*/


/*
// Assigns tile information to tiles
void Level::attachMap(Map map)
{
	// Attach input map to be the selected map
	selectedMap = map;
}*/
/*
// Checks if player is colliding with any surface
void Level::detectCollisionPlayer(Player &player)
{
	// Cycle through all surfaces
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		// Detect surface type and apply effects
		switch (selectedMap.col_CollisionData[count].type)
		{
		case PT_FLOOR: //Set player position to top of surface, zero y-velocity, stop falling and allow jumping.
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
				&& player.jumping == false)
			{
				player.position.y = selectedMap.col_CollisionData[count].collisionArea.getPosition().y - 32;
				player.velocity.y = 0;
				player.falling = false;
				player.canJump = true;
			}
			break;
		case PT_CEILING: //Set player position to bottom of surface
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
			{
				player.position.y = selectedMap.col_CollisionData[count].collisionArea.getPosition().y + 34;
				player.velocity.y = 0;
			}
			break;
		case PT_LEFT_WALL: //Set player position to right of surface
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
				&& (player.velocity.y < 2 || player.velocity.y > -2))
			{
				player.position.x = selectedMap.col_CollisionData[count].collisionArea.getPosition().x + 34;
			}
			break;
		case PT_RIGHT_WALL: //Set player position to left of surface
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
				&& (player.velocity.y < 2 || player.velocity.y > -2))
			{
				player.position.x = selectedMap.col_CollisionData[count].collisionArea.getPosition().x - 34;
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
		if (selectedMap.pla_PlatformData[count].topCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			&& player.jumping == false)
		{
			player.position.y = selectedMap.pla_PlatformData[count].topCollision.collisionArea.getPosition().y - 32;
			player.velocity.y = 0;
			player.falling = false;
			player.canJump = true;
		}
		// If player is colliding with ceiling surface
		//		--Set Position to proper
		//		--Set Velocity to 0
		if (selectedMap.pla_PlatformData[count].bottomCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
		{
			player.position.y = selectedMap.pla_PlatformData[count].bottomCollision.collisionArea.getPosition().y + 34;
			player.velocity.y = 0;
		}
		// If player is colliding with left surface
		//		--Set Position to proper
		if (selectedMap.pla_PlatformData[count].leftCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			&& (player.velocity.y < 2 || player.velocity.y > -2))
		{
			player.position.x = selectedMap.pla_PlatformData[count].leftCollision.collisionArea.getPosition().x + 34;
		}
		// If player is colliding with right surface
		//		--Set Position to proper
		if (selectedMap.pla_PlatformData[count].rightCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			&& (player.velocity.y < 2 || player.velocity.y > -2))
		{
			player.position.x = selectedMap.pla_PlatformData[count].rightCollision.collisionArea.getPosition().x - 34;
		}
	}

	// Cycle through all slopes
	for (int count = 0; count < MAXSLOPES; count++)
	{
		// Placeholders
		sf::Vector2f startPoint;
		sf::Vector2f playerPoint;
		float difference;
		float angle = selectedMap.slo_SlopeData[count].slope;

		// Assign values for the focal point of slope detection of player
		startPoint.x = selectedMap.slo_SlopeData[count].topCollision.collisionArea.getGlobalBounds().left + 8;
		startPoint.y = selectedMap.slo_SlopeData[count].bottomCollision.collisionArea.getGlobalBounds().top - 8;

		// If the player is colliding with slope and is not jumping
		if ((selectedMap.slo_SlopeData[count].topCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			|| selectedMap.slo_SlopeData[count].bottomCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			|| selectedMap.slo_SlopeData[count].leftCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) 
			|| selectedMap.slo_SlopeData[count].rightCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) 
			&& player.jumping == false )
		{
			// Right Slope
			if (selectedMap.slo_SlopeData[count].inverted == false &&
				selectedMap.slo_SlopeData[count].left_right == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.position.x + 34;
				playerPoint.y = player.position.y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& player.position.y > startPoint.y - difference - 34)
				{
					player.position.y = startPoint.y - (difference / angle) - 34;
					player.velocity.y = 0;
					player.falling = false;
					player.canJump = true;
				}
			}
			//Left Slope
			if (selectedMap.slo_SlopeData[count].inverted == false &&
				selectedMap.slo_SlopeData[count].left_right == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.position.x - 34;
				playerPoint.y = player.position.y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& player.position.y > startPoint.y + difference - 96)
				{
					player.position.y = startPoint.y + (difference / angle) - 96;
					player.velocity.y = 0;
					player.falling = false;
					player.canJump = true;
				}
			}
			//Right Inverted Slope
			if (selectedMap.slo_SlopeData[count].inverted == true &&
				selectedMap.slo_SlopeData[count].left_right == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.position.x + 34;
				playerPoint.y = player.position.y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& player.position.y < startPoint.y - difference + 96)
				{
					player.position.y = startPoint.y - difference + 96;
					player.velocity.y = 0;
				}
			}
			//Left Inverted Slope
			if (selectedMap.slo_SlopeData[count].inverted == true &&
				selectedMap.slo_SlopeData[count].left_right == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = player.position.x - 34;
				playerPoint.y = player.position.y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& player.position.y < startPoint.y + difference + 34)
				{
					player.position.y = startPoint.y + difference + 34;
					player.velocity.y = 0;
				}
			}
		}
	}
}

// Checks if player is colliding with any surface
void Level::detectCollisionEnemy(EnemyObject &enemy)
{
	// Cycle through all surfaces
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		// Detect surface type and apply effects
		switch (selectedMap.col_CollisionData[count].type)
		{
		case PT_FLOOR: //Set player position to top of surface, zero y-velocity, stop falling and allow jumping.
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds()))
				//&& enemy.jumping == false)
			{
				enemy.position.y = selectedMap.col_CollisionData[count].collisionArea.getPosition().y - 32;
				enemy.velocity.y = 0;
				enemy.falling = false;
				//enemy.canJump = true;
			}
			break;
		case PT_CEILING: //Set player position to bottom of surface
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds()))
			{
				enemy.position.y = selectedMap.col_CollisionData[count].collisionArea.getPosition().y + 34;
				enemy.velocity.y = 0;
			}
			break;
		case PT_LEFT_WALL: //Set player position to right of surface
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())
				&& (enemy.velocity.y < 2 || enemy.velocity.y > -2))
			{
				enemy.position.x = selectedMap.col_CollisionData[count].collisionArea.getPosition().x + 34;
			}
			break;
		case PT_RIGHT_WALL: //Set player position to left of surface
			if (selectedMap.col_CollisionData[count].collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())
				&& (enemy.velocity.y < 2 || enemy.velocity.y > -2))
			{
				enemy.position.x = selectedMap.col_CollisionData[count].collisionArea.getPosition().x - 34;
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
		if (selectedMap.pla_PlatformData[count].topCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds()))
			//&& player.jumping == false)
		{
			enemy.position.y = selectedMap.pla_PlatformData[count].topCollision.collisionArea.getPosition().y - 32;
			enemy.velocity.y = 0;
			enemy.falling = false;
			//enemy.canJump = true;
		}
		// If player is colliding with ceiling surface
		//		--Set Position to proper
		//		--Set Velocity to 0
		if (selectedMap.pla_PlatformData[count].bottomCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds()))
		{
			enemy.position.y = selectedMap.pla_PlatformData[count].bottomCollision.collisionArea.getPosition().y + 34;
			enemy.velocity.y = 0;
		}
		// If player is colliding with left surface
		//		--Set Position to proper
		if (selectedMap.pla_PlatformData[count].leftCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())
			&& (enemy.velocity.y < 2 || enemy.velocity.y > -2))
		{
			enemy.position.x = selectedMap.pla_PlatformData[count].leftCollision.collisionArea.getPosition().x + 34;
		}
		// If player is colliding with right surface
		//		--Set Position to proper
		if (selectedMap.pla_PlatformData[count].rightCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())
			&& (enemy.velocity.y < 2 || enemy.velocity.y > -2))
		{
			enemy.position.x = selectedMap.pla_PlatformData[count].rightCollision.collisionArea.getPosition().x - 34;
		}
	}

	// Cycle through all slopes
	for (int count = 0; count < MAXSLOPES; count++)
	{
		// Placeholders
		sf::Vector2f startPoint;
		sf::Vector2f playerPoint;
		float difference;
		float angle = selectedMap.slo_SlopeData[count].slope;

		// Assign values for the focal point of slope detection of player
		startPoint.x = selectedMap.slo_SlopeData[count].topCollision.collisionArea.getGlobalBounds().left + 8;
		startPoint.y = selectedMap.slo_SlopeData[count].bottomCollision.collisionArea.getGlobalBounds().top - 8;

		// If the player is colliding with slope and is not jumping
		if ((selectedMap.slo_SlopeData[count].topCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())
			|| selectedMap.slo_SlopeData[count].bottomCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())
			|| selectedMap.slo_SlopeData[count].leftCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())
			|| selectedMap.slo_SlopeData[count].rightCollision.collisionArea.getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())))
			//&& player.jumping == false)
		{
			// Right Slope
			if (selectedMap.slo_SlopeData[count].inverted == false &&
				selectedMap.slo_SlopeData[count].left_right == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.position.x + 34;
				playerPoint.y = enemy.position.y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& enemy.position.y > startPoint.y - difference - 34)
				{
					enemy.position.y = startPoint.y - (difference / angle) - 34;
					enemy.velocity.y = 0;
					enemy.falling = false;
					//enemy.canJump = true;
				}
			}
			//Left Slope
			if (selectedMap.slo_SlopeData[count].inverted == false &&
				selectedMap.slo_SlopeData[count].left_right == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.position.x - 34;
				playerPoint.y = enemy.position.y + 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				//		--Allow player to jump and not be in falling state.
				if ((difference > 0 && difference < (64 * angle) + 4)
					&& enemy.position.y > startPoint.y + difference - 96)
				{
					enemy.position.y = startPoint.y + (difference / angle) - 96;
					enemy.velocity.y = 0;
					enemy.falling = false;
					//enemy.canJump = true;
				}
			}
			//Right Inverted Slope
			if (selectedMap.slo_SlopeData[count].inverted == true &&
				selectedMap.slo_SlopeData[count].left_right == RIGHT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.position.x + 34;
				playerPoint.y = enemy.position.y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& enemy.position.y < startPoint.y - difference + 96)
				{
					enemy.position.y = startPoint.y - difference + 96;
					enemy.velocity.y = 0;
				}
			}
			//Left Inverted Slope
			if (selectedMap.slo_SlopeData[count].inverted == true &&
				selectedMap.slo_SlopeData[count].left_right == LEFT)
			{
				// Assign focal point for player detection of slope
				playerPoint.x = enemy.position.x - 34;
				playerPoint.y = enemy.position.y - 34;

				// Calculate how far player is in the slope's tile
				difference = playerPoint.x - startPoint.x;

				// If the player is within a certain units of the focal point,
				// and the player's position is below where it should be:
				//		--Set position to proper 
				//		--Set Velocity to 0
				if ((difference > 0 && difference < 68)
					&& enemy.position.y < startPoint.y + difference + 34)
				{
					enemy.position.y = startPoint.y + difference + 34;
					enemy.velocity.y = 0;
				}
			}
		}
	}
}*/