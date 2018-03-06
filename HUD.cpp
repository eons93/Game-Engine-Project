#include "stdafx.h"
#include "HUD.h"
#include <iostream>
#include "GeneralFunctions.h"
#include "Player.h"
#include "Engine.h"


HUD::HUD()
{
	if (!fon_HUD_Font.loadFromFile("The Citadels.otf"))
	{
		std::cout << "font failed to load" << std::endl;
	}

	txt_TopLeft[1].setCharacterSize(40);
	txt_TopLeft[1].setFillColor(sf::Color(255, 0, 0));
	txt_TopLeft[1].setString("Health");

	// Position Stats
	{
		txt_TopRight[1].setCharacterSize(20);
		txt_TopRight[1].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[1].x = -24;
		vec_BasePositionTR[1].y = 24;

		txt_TopRight[2].setCharacterSize(20);
		txt_TopRight[2].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[2].x = 0;
		vec_BasePositionTR[2].y = 48;

		txt_TopRight[3].setCharacterSize(20);
		txt_TopRight[3].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[3].x = 0;
		vec_BasePositionTR[3].y = 72;
	}

	// Velocity Stats
	{
		txt_TopRight[4].setCharacterSize(20);
		txt_TopRight[4].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[4].x = -24;
		vec_BasePositionTR[4].y = 96;

		txt_TopRight[5].setCharacterSize(20);
		txt_TopRight[5].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[5].x = 0;
		vec_BasePositionTR[5].y = 120;

		txt_TopRight[6].setCharacterSize(20);
		txt_TopRight[6].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[6].x = 0;
		vec_BasePositionTR[6].y = 144;
	}

	// State Stats
	{
		txt_TopRight[7].setCharacterSize(16);
		txt_TopRight[7].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[7].x = 0;
		vec_BasePositionTR[7].y = 180;

		txt_TopRight[8].setCharacterSize(16);
		txt_TopRight[8].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[8].x = 0;
		vec_BasePositionTR[8].y = 200;

		txt_TopRight[9].setCharacterSize(16);
		txt_TopRight[9].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[9].x = 0;
		vec_BasePositionTR[9].y = 220;

		txt_TopRight[10].setCharacterSize(16);
		txt_TopRight[10].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[10].x = 0;
		vec_BasePositionTR[10].y = 240;

		txt_TopRight[11].setCharacterSize(16);
		txt_TopRight[11].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[11].x = 0;
		vec_BasePositionTR[11].y = 260;

		txt_TopRight[12].setCharacterSize(16);
		txt_TopRight[12].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[12].x = 0;
		vec_BasePositionTR[12].y = 280;

		txt_TopRight[13].setCharacterSize(16);
		txt_TopRight[13].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[13].x = 0;
		vec_BasePositionTR[13].y = 300;

		txt_TopRight[14].setCharacterSize(16);
		txt_TopRight[14].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[14].x = 0;
		vec_BasePositionTR[14].y = 320;

		txt_TopRight[15].setCharacterSize(16);
		txt_TopRight[15].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[15].x = 0;
		vec_BasePositionTR[15].y = 340;

		txt_TopRight[16].setCharacterSize(16);
		txt_TopRight[16].setFillColor(sf::Color(255, 0, 0));
		vec_BasePositionTR[16].x = 0;
		vec_BasePositionTR[16].y = 360;
	}

	// Sets default values 
	for (int count = 0; count < 20; count++)
	{
		txt_TopLeft[count].setFont(fon_HUD_Font);
		txt_TopRight[count].setFont(fon_HUD_Font);

		txt_TopLeft[count].setOrigin(0, 0);
		txt_TopRight[count].setOrigin(txt_TopRight[count].getGlobalBounds().width , 0);
		
		txt_TopLeft[count].setOutlineColor(sf::Color(0, 0, 0));
		txt_TopRight[count].setOutlineColor(sf::Color(0, 0, 0));
		
		txt_TopLeft[count].setOutlineThickness(1);
		txt_TopRight[count].setOutlineThickness(1);
	}
}

// View that is passed in become anchor 
void HUD::AttachCamera(sf::View camera)
{
	// Turn Camera Variables into simpler terms
	float camSizeX = camera.getSize().x;
	float camSizeY = camera.getSize().y;
	float camCenX = camera.getCenter().x;
	float camCenY = camera.getCenter().y;

	// Use simplified camera variables to define screen dimensions
	flo_Top = camCenY - (camSizeY / 2);
	flo_Bottom = camCenY + (camSizeY / 2);
	flo_Right = -16 + camCenX + (camSizeX / 2);
	flo_Left = 16 + camCenX - (camSizeX / 2);
}

// Update values from player for display
void HUD::UpdateHUD(Player HUDplayer)
{	
	txt_TopRight[1].setString("Position: " + StringConvert(HUDplayer.vec_Position.x / 64) + ", " + StringConvert(HUDplayer.vec_Position.y / 64));
	txt_TopRight[2].setString("X Range: " + StringConvert(HUDplayer.flo_MinX) + ", " + StringConvert(HUDplayer.flo_MaxX));
	txt_TopRight[3].setString("Y Range: " + StringConvert(HUDplayer.flo_MinY) + ", " + StringConvert(HUDplayer.flo_MaxY));

	txt_TopRight[4].setString("Velocity: " + StringConvert(HUDplayer.vec_Velocity.x) + "   , " + StringConvert(HUDplayer.vec_Velocity.y) + "    ");
	txt_TopRight[5].setString("X Range: " + StringConvert(HUDplayer.flo_MinVelX) + ", " + StringConvert(HUDplayer.flo_MaxVelX));
	txt_TopRight[6].setString("Y Range: " + StringConvert(HUDplayer.flo_MinVelY) + ", " + StringConvert(HUDplayer.flo_MaxVelY));

	txt_TopRight[7].setString("Facing:       " + StringConvert(HUDplayer.bol_Facing));
	txt_TopRight[8].setString("Jumping:      " + StringConvert(HUDplayer.bol_Jumping));
	txt_TopRight[9].setString("Ducking:      " + StringConvert(HUDplayer.bol_Ducking));
	txt_TopRight[10].setString("Rolling:      " + StringConvert(HUDplayer.bol_Rolling));
	txt_TopRight[11].setString("Blocking:     " + StringConvert(HUDplayer.bol_Blocking));
	txt_TopRight[12].setString("Falling:      " + StringConvert(HUDplayer.bol_Falling));
	txt_TopRight[13].setString("Shooting:     " + StringConvert(HUDplayer.bol_Shooting));
	txt_TopRight[14].setString("Meleeing:     " + StringConvert(HUDplayer.bol_Meleeing));
	txt_TopRight[15].setString("Moving Left:  " + StringConvert(HUDplayer.bol_MovingL));
	txt_TopRight[16].setString("Moving Right: " + StringConvert(HUDplayer.bol_MovingR));

	// Lines each item up properly within screen
	for (int count = 0; count < 20; count++)
	{
		vec_TruePositionTL[count].x = flo_Left + vec_BasePositionTL[count].x;
		vec_TruePositionTL[count].y = flo_Top + vec_BasePositionTL[count].y;

		vec_TruePositionTR[count].x = flo_Right + vec_BasePositionTR[count].x;
		vec_TruePositionTR[count].y = flo_Top + vec_BasePositionTR[count].y;
	}

	// Sets positions and origins to line everything up
	for (int count = 0; count < 20; count++)
	{
		txt_TopLeft[count].setPosition(vec_TruePositionTL[count]);
		txt_TopRight[count].setPosition(vec_TruePositionTR[count]);

		txt_TopLeft[count].setOrigin(0, 0);
		txt_TopRight[count].setOrigin(txt_TopRight[count].getGlobalBounds().width, 0);
	}
}