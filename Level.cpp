#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "Engine.h"
#include "GeneralFunctions.h"

Level::Level()
{
	
}

// Applies map's textures 
void Level::attachTexture()
{
	background.setTexture(&selectedMap.bgImage);
	levelStructure.setTexture(selectedMap.levelImage);
	//levelStructure.setPosition(0, 0);
}

// Assigns tile information to tiles
void Level::attachMap(Map map)
{
	// Attach input map to be the selected map
	selectedMap = map;

	selectedMap.CollisionData.resize(MAXCOLLISIONS);

	
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		if (count < 20)
		{
			map.CollisionData[count].identifier.setString("Collision (Floor): " + stringConvert(count));
		}
		else if (count < 40)
		{
			map.CollisionData[count].identifier.setString("Collision (Left): " + stringConvert(count - 20));
		}
		else if (count < 60)
		{
			map.CollisionData[count].identifier.setString("Collision (Right): " + stringConvert(count - 40));
		}
		else if (count < 80)
		{
			map.CollisionData[count].identifier.setString("Collision (Ceiling): " + stringConvert(count - 60));
		}
		else
		{
			map.CollisionData[count].identifier.setString("Collision (misc): " + stringConvert(count - 60));
		}
	}
	for (int count = 0; count < MAXPLATFORMS; count++)
	{
		map.PlatformData[count].bottomCollision.identifier.setString("Collision (Ceiling): " + stringConvert(count));
		map.PlatformData[count].topCollision.identifier.setString("Collision (Floor): " + stringConvert(count));
		map.PlatformData[count].leftCollision.identifier.setString("Collision (Left): " + stringConvert(count));
		map.PlatformData[count].rightCollision.identifier.setString("Collision (Left): " + stringConvert(count));
	}
	for (int count = 0; count < MAXSLOPES; count++)
	{
		map.SlopeData[count].bottomCollision.identifier.setString("Collision (Ceiling): " + stringConvert(count));
		map.SlopeData[count].topCollision.identifier.setString("Collision (Floor): " + stringConvert(count));
		map.SlopeData[count].leftCollision.identifier.setString("Collision (Left): " + stringConvert(count));
		map.SlopeData[count].rightCollision.identifier.setString("Collision (Left): " + stringConvert(count));
	}
	
}

// Checks if player is colliding with any surface
void Level::detectCollision1(Player &player)
{
	// Cycle through all surfaces
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		// Detect surface type and apply effects
		switch (selectedMap.CollisionData[count].type)
		{
		case FLOOR: //Set player position to top of surface, zero y-velocity, stop falling and allow jumping.
			if (selectedMap.CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
				&& player.jumping == false)
			{
				player.position.y = selectedMap.CollisionData[count].collisionArea.getPosition().y - 32;
				player.velocity.y = 0;
				player.falling = false;
				player.canJump = true;
			}
			break;
		case CEILING: //Set player position to bottom of surface
			if (selectedMap.CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
			{
				player.position.y = selectedMap.CollisionData[count].collisionArea.getPosition().y + 34;
				player.velocity.y = 0;
			}
			break;
		case LEFT_WALL: //Set player position to right of surface
			if (selectedMap.CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
				&& (player.velocity.y < 2 || player.velocity.y > -2))
			{
				player.position.x = selectedMap.CollisionData[count].collisionArea.getPosition().x + 34;
			}
			break;
		case RIGHT_WALL: //Set player position to left of surface
			if (selectedMap.CollisionData[count].collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
				&& (player.velocity.y < 2 || player.velocity.y > -2))
			{
				player.position.x = selectedMap.CollisionData[count].collisionArea.getPosition().x - 34;
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
		if (selectedMap.PlatformData[count].topCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			&& player.jumping == false)
		{
			player.position.y = selectedMap.PlatformData[count].topCollision.collisionArea.getPosition().y - 32;
			player.velocity.y = 0;
			player.falling = false;
			player.canJump = true;
		}
		// If player is colliding with ceiling surface
		//		--Set Position to proper
		//		--Set Velocity to 0
		if (selectedMap.PlatformData[count].bottomCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
		{
			player.position.y = selectedMap.PlatformData[count].bottomCollision.collisionArea.getPosition().y + 34;
			player.velocity.y = 0;
		}
		// If player is colliding with left surface
		//		--Set Position to proper
		if (selectedMap.PlatformData[count].leftCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			&& (player.velocity.y < 2 || player.velocity.y > -2))
		{
			player.position.x = selectedMap.PlatformData[count].leftCollision.collisionArea.getPosition().x + 34;
		}
		// If player is colliding with right surface
		//		--Set Position to proper
		if (selectedMap.PlatformData[count].rightCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			&& (player.velocity.y < 2 || player.velocity.y > -2))
		{
			player.position.x = selectedMap.PlatformData[count].rightCollision.collisionArea.getPosition().x - 34;
		}
	}

	// Cycle through all slopes
	for (int count = 0; count < MAXSLOPES; count++)
	{
		// Placeholders
		sf::Vector2f startPoint;
		sf::Vector2f playerPoint;
		float difference;
		float angle = selectedMap.SlopeData[count].slope;

		// Assign values for the focal point of slope detection of player
		startPoint.x = selectedMap.SlopeData[count].topCollision.collisionArea.getGlobalBounds().left + 8;
		startPoint.y = selectedMap.SlopeData[count].bottomCollision.collisionArea.getGlobalBounds().top - 8;

		// If the player is colliding with slope and is not jumping
		if ((selectedMap.SlopeData[count].topCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			|| selectedMap.SlopeData[count].bottomCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())
			|| selectedMap.SlopeData[count].leftCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds()) 
			|| selectedMap.SlopeData[count].rightCollision.collisionArea.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) 
			&& player.jumping == false )
		{
			// Right Slope
			if (selectedMap.SlopeData[count].inverted == false &&
				selectedMap.SlopeData[count].left_right == RIGHT)
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
			if (selectedMap.SlopeData[count].inverted == false &&
				selectedMap.SlopeData[count].left_right == LEFT)
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
			if (selectedMap.SlopeData[count].inverted == true &&
				selectedMap.SlopeData[count].left_right == RIGHT)
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
			if (selectedMap.SlopeData[count].inverted == true &&
				selectedMap.SlopeData[count].left_right == LEFT)
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