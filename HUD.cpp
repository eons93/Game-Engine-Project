#include "stdafx.h"
#include "HUD.h"
#include <iostream>
#include "GeneralFunctions.h"
#include "Player.h"


HUD::HUD()
{
	if (!font.loadFromFile("The Citadels.otf"))
	{
		std::cout << "font failed to load" << std::endl;
	}

	textTL[1].setCharacterSize(40);
	textTL[1].setFillColor(sf::Color(255, 0, 0));
	textTL[1].setString("Health");

	// Position Stats
	{
		textTR[1].setCharacterSize(20);
		textTR[1].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[1].x = -24;
		basePositionTR[1].y = 24;

		textTR[2].setCharacterSize(20);
		textTR[2].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[2].x = 0;
		basePositionTR[2].y = 48;

		textTR[3].setCharacterSize(20);
		textTR[3].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[3].x = 0;
		basePositionTR[3].y = 72;
	}

	// Velocity Stats
	{
		textTR[4].setCharacterSize(20);
		textTR[4].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[4].x = -24;
		basePositionTR[4].y = 96;

		textTR[5].setCharacterSize(20);
		textTR[5].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[5].x = 0;
		basePositionTR[5].y = 120;

		textTR[6].setCharacterSize(20);
		textTR[6].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[6].x = 0;
		basePositionTR[6].y = 144;
	}

	// State Stats
	{
		textTR[7].setCharacterSize(16);
		textTR[7].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[7].x = 0;
		basePositionTR[7].y = 180;

		textTR[8].setCharacterSize(16);
		textTR[8].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[8].x = 0;
		basePositionTR[8].y = 200;

		textTR[9].setCharacterSize(16);
		textTR[9].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[9].x = 0;
		basePositionTR[9].y = 220;

		textTR[10].setCharacterSize(16);
		textTR[10].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[10].x = 0;
		basePositionTR[10].y = 240;

		textTR[11].setCharacterSize(16);
		textTR[11].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[11].x = 0;
		basePositionTR[11].y = 260;

		textTR[12].setCharacterSize(16);
		textTR[12].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[12].x = 0;
		basePositionTR[12].y = 280;

		textTR[13].setCharacterSize(16);
		textTR[13].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[13].x = 0;
		basePositionTR[13].y = 300;

		textTR[14].setCharacterSize(16);
		textTR[14].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[14].x = 0;
		basePositionTR[14].y = 320;

		textTR[15].setCharacterSize(16);
		textTR[15].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[15].x = 0;
		basePositionTR[15].y = 340;

		textTR[16].setCharacterSize(16);
		textTR[16].setFillColor(sf::Color(255, 0, 0));
		basePositionTR[16].x = 0;
		basePositionTR[16].y = 360;
	}

	// Misc testers
	textBL[1].setCharacterSize(20);
	textBL[1].setFillColor(sf::Color(255, 0, 0));
	textBL[1].setString("DIFFERENCE GAME ENGINE");

	textBR[1].setCharacterSize(20);
	textBR[1].setFillColor(sf::Color(255, 0, 0));
	textBR[1].setString("PLEASE FUCK QUIETLY");

	// Sets default values 
	for (int count = 0; count < 20; count++)
	{
		textTL[count].setFont(font);
		textTR[count].setFont(font);
		textBL[count].setFont(font);
		textBR[count].setFont(font);

		textTL[count].setOrigin(0, 0);
		textTR[count].setOrigin(textTR[count].getGlobalBounds().width , 0);
		textBL[count].setOrigin(0, (textBL[count].getGlobalBounds().height * 2));
		textBR[count].setOrigin(textBR[count].getGlobalBounds().width, (textBR[count].getGlobalBounds().height * 2));

		textTL[count].setOutlineColor(sf::Color(0, 0, 0));
		textTR[count].setOutlineColor(sf::Color(0, 0, 0));
		textBL[count].setOutlineColor(sf::Color(0, 0, 0));
		textBR[count].setOutlineColor(sf::Color(0, 0, 0));

		textTL[count].setOutlineThickness(1);
		textTR[count].setOutlineThickness(1);
		textBL[count].setOutlineThickness(1);
		textBR[count].setOutlineThickness(1);
	}
}

// View that is passed in become anchor 
void HUD::attachCamera(sf::View camera)
{
	// Turn Camera Variables into simpler terms
	float camSizeX = camera.getSize().x;
	float camSizeY = camera.getSize().y;
	float camCenX = camera.getCenter().x;
	float camCenY = camera.getCenter().y;

	// Use simplified camera variables to define screen dimensions
	top = camCenY - (camSizeY / 2);
	bottom = camCenY + (camSizeY / 2);
	right = -16 + camCenX + (camSizeX / 2);
	left = 16 + camCenX - (camSizeX / 2);
}

// Update values from player for display
void HUD::updateHUD(Player HUDplayer)
{	
	textTR[1].setString("Position: " + stringConvert(HUDplayer.position.x / 64) + ", " + stringConvert(HUDplayer.position.y / 64));
	textTR[2].setString("X Range: " + stringConvert(HUDplayer.minX) + ", " + stringConvert(HUDplayer.maxX));
	textTR[3].setString("Y Range: " + stringConvert(HUDplayer.minY) + ", " + stringConvert(HUDplayer.maxY));

	textTR[4].setString("Velocity: " + stringConvert(HUDplayer.velocity.x) + "   , " + stringConvert(HUDplayer.velocity.y) + "    ");
	textTR[5].setString("X Range: " + stringConvert(HUDplayer.minVelX) + ", " + stringConvert(HUDplayer.maxVelX));
	textTR[6].setString("Y Range: " + stringConvert(HUDplayer.minVelY) + ", " + stringConvert(HUDplayer.maxVelY));

	textTR[7].setString("Facing:       " + stringConvert(HUDplayer.facing));
	textTR[8].setString("Jumping:      " + stringConvert(HUDplayer.jumping));
	textTR[9].setString("Ducking:      " + stringConvert(HUDplayer.ducking));
	textTR[10].setString("Rolling:      " + stringConvert(HUDplayer.rolling));
	textTR[11].setString("Blocking:     " + stringConvert(HUDplayer.blocking));
	textTR[12].setString("Falling:      " + stringConvert(HUDplayer.falling));
	textTR[13].setString("Shooting:     " + stringConvert(HUDplayer.shooting));
	textTR[14].setString("Meleeing:     " + stringConvert(HUDplayer.meleeing));
	textTR[15].setString("Moving Left:  " + stringConvert(HUDplayer.movingL));
	textTR[16].setString("Moving Right: " + stringConvert(HUDplayer.movingR));

	// Lines each item up properly within screen
	for (int count = 0; count < 20; count++)
	{
		truePositionTL[count].x = left + basePositionTL[count].x;
		truePositionTL[count].y = top + basePositionTL[count].y;

		truePositionTR[count].x = right + basePositionTR[count].x;
		truePositionTR[count].y = top + basePositionTR[count].y;

		truePositionBL[count].x = left + basePositionBL[count].x;
		truePositionBL[count].y = bottom + basePositionBL[count].y;

		truePositionBR[count].x = right + basePositionBR[count].x;
		truePositionBR[count].y = bottom + basePositionBR[count].y;
	}

	// Sets positions and origins to line everything up
	for (int count = 0; count < 20; count++)
	{
		textTL[count].setPosition(truePositionTL[count]);
		textTR[count].setPosition(truePositionTR[count]);
		textBL[count].setPosition(truePositionBL[count]);
		textBR[count].setPosition(truePositionBR[count]);

		textTL[count].setOrigin(0, 0);
		textTR[count].setOrigin(textTR[count].getGlobalBounds().width, 0);
		textBL[count].setOrigin(0, (textBL[count].getGlobalBounds().height * 2));
		textBR[count].setOrigin(textBR[count].getGlobalBounds().width, (textBR[count].getGlobalBounds().height * 2));
	}
}

