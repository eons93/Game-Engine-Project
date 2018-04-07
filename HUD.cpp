#include "stdafx.h"
#include "HUD.h"
#include <iostream>
#include "GeneralFunctions.h"
#include "Player.h"
#include "Engine.h"


HUD::HUD()
{
	ht_CurrentMode = RELEASE;

	if (!fon_HUD_Font.loadFromFile("The Citadels.otf"))
	{
		std::cout << "font failed to load" << std::endl;
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

	for (int count = 0; count < 5; count++)
	{
		dr_LastOutput[count].TotalDmg = 0;
		dr_LastOutput[count].ShieldDmg = 0;
		dr_LastOutput[count].HealthDmg = 0;
		dr_LastOutput[count].Hit = true;
		dr_LastOutput[count].Critical = false;
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
	vec_Center.x = camCenX;
	vec_Center.y = camCenY;
}

// Update values from player for display
void HUD::UpdateHUD(Player HUDplayer)
{
	// Universal Components

		// GameOver
		txt_GameOver.setFont(fon_HUD_Font);
		txt_GameOver.setCharacterSize(120);
		txt_GameOver.setFillColor(sf::Color::Transparent);
		txt_GameOver.setOutlineThickness(-1);
		txt_GameOver.setOutlineColor(sf::Color::Magenta);
		txt_GameOver.setOrigin(sf::Vector2f(txt_GameOver.getGlobalBounds().width / 2, txt_GameOver.getGlobalBounds().height / 2));
		txt_GameOver.setPosition(vec_Center);
		txt_GameOver.setString("GAMEOVER");

		//Health and Shields Bar
		{
		txt_HealthBar.setString("Health");
		txt_HealthBar.setPosition(flo_Left, flo_Top);
		txt_HealthBar.setFillColor(sf::Color(0, 255, 0));
		txt_ShieldsBar.setString("Shields");
		txt_ShieldsBar.setPosition(flo_Left, flo_Top + 90);
		txt_ShieldsBar.setFillColor(sf::Color(0, 255, 0));
		{
			txt_HealthBar.setFont(fon_HUD_Font);
			txt_HealthBar.setOutlineColor(sf::Color(255, 255, 255));
			txt_HealthBar.setCharacterSize(20);
			txt_HealthBar.setOutlineThickness(2);
			txt_ShieldsBar.setFont(fon_HUD_Font);
			txt_ShieldsBar.setOutlineColor(sf::Color(255, 255, 255));
			txt_ShieldsBar.setCharacterSize(20);
			txt_ShieldsBar.setOutlineThickness(2);
		}

		rec_HealthBar.setPosition(flo_Left, flo_Top + 31);
		rec_HealthBar.setSize(sf::Vector2f(HUDplayer.GetCurrentHealth() * 5, 20));
		rec_HealthBar.setFillColor(HealthPercentColor(HUDplayer.GetCurrentHealth() * 100 / HUDplayer.GetAttributes().Health));
		rec_ShieldsBar.setPosition(flo_Left, flo_Top + 65);
		rec_ShieldsBar.setSize(sf::Vector2f(HUDplayer.GetCurrentShields() * 5, 20));
		rec_ShieldsBar.setFillColor(ShieldPercentColor(HUDplayer.GetCurrentShields() * 100 / HUDplayer.GetAttributes().Shield));

		rec_HealthBG.setPosition(flo_Left, flo_Top + 31);
		rec_HealthBG.setSize(sf::Vector2f(HUDplayer.GetAttributes().Health * 5, 20));
		rec_HealthBG.setFillColor(sf::Color(0, 0, 0));
		rec_ShieldsBG.setPosition(flo_Left, flo_Top + 65);
		rec_ShieldsBG.setSize(sf::Vector2f(HUDplayer.GetAttributes().Shield * 5, 20));
		rec_ShieldsBG.setFillColor(sf::Color(0, 0, 0));
	}

	// Right-Bound Objects are dependant on the HUD Mode
	switch (ht_CurrentMode)
	{
	case RELEASE:
		for (int count = 0; count < 20; count++)
		{
			txt_TopRight[count].setString(" ");
		}
		break;
	case MOVEMENT:
		CheckMinMax(HUDplayer.GetPosition(), HUDplayer.GetVelocity());

		// Position Section
		txt_TopRight[0].setString("Position: " + StringConvert(HUDplayer.GetPosition().x / 64) + ", " + StringConvert(HUDplayer.GetPosition().y / 64));
		txt_TopRight[1].setString("X Range: " + StringConvert(flo_MinX) + ", " + StringConvert(flo_MaxX));
		txt_TopRight[2].setString("Y Range: " + StringConvert(flo_MinY) + ", " + StringConvert(flo_MaxY));

		{
			txt_TopRight[0].setCharacterSize(20);
			txt_TopRight[1].setCharacterSize(20);
			txt_TopRight[2].setCharacterSize(20);

			txt_TopRight[0].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[1].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[2].setFillColor(sf::Color(255, 0, 0));

			vec_BasePositionTR[0].x = -24;
			vec_BasePositionTR[0].y = 24;
			vec_BasePositionTR[1].x = 0;
			vec_BasePositionTR[1].y = 48;
			vec_BasePositionTR[2].x = 0;
			vec_BasePositionTR[2].y = 72;
		}

		// Velocity Section
		txt_TopRight[3].setString("Velocity: " + StringConvert(HUDplayer.GetVelocity().x) + "   , " + StringConvert(HUDplayer.GetVelocity().y) + "    ");
		txt_TopRight[4].setString("X Range: " + StringConvert(flo_MinVelX) + ", " + StringConvert(flo_MaxVelX));
		txt_TopRight[5].setString("Y Range: " + StringConvert(flo_MinVelY) + ", " + StringConvert(flo_MaxVelY));

		{
			txt_TopRight[3].setCharacterSize(20);
			txt_TopRight[4].setCharacterSize(20);
			txt_TopRight[5].setCharacterSize(20);

			txt_TopRight[3].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[4].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[5].setFillColor(sf::Color(255, 0, 0));

			vec_BasePositionTR[3].x = -24;
			vec_BasePositionTR[3].y = 96;
			vec_BasePositionTR[4].x = 0;
			vec_BasePositionTR[4].y = 120;
			vec_BasePositionTR[5].x = 0;
			vec_BasePositionTR[5].y = 144;
		}

		// States Section
		txt_TopRight[6].setString("Facing:       " + StringConvert(HUDplayer.GetState().Facing));
		txt_TopRight[7].setString("Jumping:      " + StringConvert(HUDplayer.GetState().Jumping));
		txt_TopRight[8].setString("Ducking:      " + StringConvert(HUDplayer.GetState().Ducking));
		txt_TopRight[9].setString("Rolling:      " + StringConvert(HUDplayer.GetState().Rolling));
		txt_TopRight[10].setString("Blocking:     " + StringConvert(HUDplayer.GetState().Blocking));
		txt_TopRight[11].setString("Falling:      " + StringConvert(HUDplayer.GetState().Falling));
		txt_TopRight[12].setString("Shooting:     " + StringConvert(HUDplayer.GetState().Shooting));
		txt_TopRight[13].setString("Meleeing:     " + StringConvert(HUDplayer.GetState().Meleeing));
		txt_TopRight[14].setString("Moving Left:  " + StringConvert(HUDplayer.GetState().MovingL));
		txt_TopRight[15].setString("Moving Right: " + StringConvert(HUDplayer.GetState().MovingR));

		{
			txt_TopRight[6].setCharacterSize(16);
			txt_TopRight[7].setCharacterSize(16);
			txt_TopRight[8].setCharacterSize(16);
			txt_TopRight[9].setCharacterSize(16);
			txt_TopRight[10].setCharacterSize(16);
			txt_TopRight[11].setCharacterSize(16);
			txt_TopRight[12].setCharacterSize(16);
			txt_TopRight[13].setCharacterSize(16);
			txt_TopRight[14].setCharacterSize(16);
			txt_TopRight[15].setCharacterSize(16);

			txt_TopRight[6].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[7].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[8].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[9].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[10].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[11].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[12].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[13].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[14].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[15].setFillColor(sf::Color(255, 0, 0));

			vec_BasePositionTR[6].x = 0;
			vec_BasePositionTR[6].y = 180;
			vec_BasePositionTR[7].x = 0;
			vec_BasePositionTR[7].y = 200;
			vec_BasePositionTR[8].x = 0;
			vec_BasePositionTR[8].y = 220;
			vec_BasePositionTR[9].x = 0;
			vec_BasePositionTR[9].y = 240;
			vec_BasePositionTR[10].x = 0;
			vec_BasePositionTR[10].y = 260;
			vec_BasePositionTR[11].x = 0;
			vec_BasePositionTR[11].y = 280;
			vec_BasePositionTR[12].x = 0;
			vec_BasePositionTR[12].y = 300;
			vec_BasePositionTR[13].x = 0;
			vec_BasePositionTR[13].y = 320;
			vec_BasePositionTR[12].x = 0;
			vec_BasePositionTR[12].y = 300;
			vec_BasePositionTR[13].x = 0;
			vec_BasePositionTR[13].y = 320;
			vec_BasePositionTR[14].x = 0;
			vec_BasePositionTR[14].y = 340;
			vec_BasePositionTR[15].x = 0;
			vec_BasePositionTR[15].y = 360;
		}

		// Clear Unused Lines
		for (int count = 16; count < 20; count++)
		{
			txt_TopRight[count].setString("");
			txt_TopRight[count].setCharacterSize(0);
			txt_TopRight[count].setFillColor(sf::Color(0, 0, 0));
			vec_BasePositionTR[count].x = 0;
			vec_BasePositionTR[count].y = 0;
		}
		break;
	case COMBAT:
		// Output Damage Report
		txt_TopRight[0].setString("Damage Dealt");
		txt_TopRight[1].setString("|Hit|--|Crit|--|Total|--|Shield|--|Health| ");
		txt_TopRight[2].setString("Last 1     " 
			+ StringConvert(dr_LastOutput[0].Hit) + "           " 
			+ StringConvert(dr_LastOutput[0].Critical) + "                "
			+ StringConvert(dr_LastOutput[0].TotalDmg) + "                " 
			+ StringConvert(dr_LastOutput[0].ShieldDmg) + "                 "
			+ StringConvert(dr_LastOutput[0].HealthDmg) + "   ");
		txt_TopRight[3].setString("Last 2     " 
			+ StringConvert(dr_LastOutput[1].Hit) + "           "
			+ StringConvert(dr_LastOutput[1].Critical) + "                "
			+ StringConvert(dr_LastOutput[1].TotalDmg) + "                "
			+ StringConvert(dr_LastOutput[1].ShieldDmg) + "                 "
			+ StringConvert(dr_LastOutput[1].HealthDmg) + "   ");
		txt_TopRight[4].setString("Last 3     " 
			+ StringConvert(dr_LastOutput[2].Hit) + "           "
			+ StringConvert(dr_LastOutput[2].Critical) + "                "
			+ StringConvert(dr_LastOutput[2].TotalDmg) + "                "
			+ StringConvert(dr_LastOutput[2].ShieldDmg) + "                 "
			+ StringConvert(dr_LastOutput[2].HealthDmg) + "   ");
		txt_TopRight[5].setString("Last 4     " 
			+ StringConvert(dr_LastOutput[3].Hit) + "           "
			+ StringConvert(dr_LastOutput[3].Critical) + "                "
			+ StringConvert(dr_LastOutput[3].TotalDmg) + "                "
			+ StringConvert(dr_LastOutput[3].ShieldDmg) + "                 "
			+ StringConvert(dr_LastOutput[3].HealthDmg) + "   ");
		txt_TopRight[6].setString("Last 5     " 
			+ StringConvert(dr_LastOutput[4].Hit) + "           "
			+ StringConvert(dr_LastOutput[4].Critical) + "                "
			+ StringConvert(dr_LastOutput[4].TotalDmg) + "                "
			+ StringConvert(dr_LastOutput[4].ShieldDmg) + "                 "
			+ StringConvert(dr_LastOutput[4].HealthDmg) + "   ");

		{
			txt_TopRight[0].setCharacterSize(20);
			txt_TopRight[1].setCharacterSize(20);
			txt_TopRight[2].setCharacterSize(20);
			txt_TopRight[3].setCharacterSize(20);
			txt_TopRight[4].setCharacterSize(20);
			txt_TopRight[5].setCharacterSize(20);
			txt_TopRight[6].setCharacterSize(20);

			txt_TopRight[0].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[1].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[2].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[3].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[4].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[5].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[6].setFillColor(sf::Color(255, 0, 0));

			vec_BasePositionTR[0].x = 0;
			vec_BasePositionTR[0].y = 24;
			vec_BasePositionTR[1].x = 0;
			vec_BasePositionTR[1].y = 48;
			vec_BasePositionTR[2].x = 0;
			vec_BasePositionTR[2].y = 72;
			vec_BasePositionTR[3].x = 0;
			vec_BasePositionTR[3].y = 96;
			vec_BasePositionTR[4].x = 0;
			vec_BasePositionTR[4].y = 120;
			vec_BasePositionTR[5].x = 0;
			vec_BasePositionTR[5].y = 144;
			vec_BasePositionTR[6].x = 0;
			vec_BasePositionTR[6].y = 168;
		}

		// Input Damage Report
		txt_TopRight[7].setString("Damage Recieved");
		txt_TopRight[8].setString("|Hit|--|Crit|--|Total|--|Shield|--|Health| ");
		txt_TopRight[9].setString("Last 1     "
			+ StringConvert(dr_LastInput[0].Hit) + "           "
			+ StringConvert(dr_LastInput[0].Critical) + "                "
			+ StringConvert(dr_LastInput[0].TotalDmg) + "                "
			+ StringConvert(dr_LastInput[0].ShieldDmg) + "                 "
			+ StringConvert(dr_LastInput[0].HealthDmg) + "   ");
		txt_TopRight[10].setString("Last 2     "
			+ StringConvert(dr_LastInput[1].Hit) + "           "
			+ StringConvert(dr_LastInput[1].Critical) + "                "
			+ StringConvert(dr_LastInput[1].TotalDmg) + "                "
			+ StringConvert(dr_LastInput[1].ShieldDmg) + "                 "
			+ StringConvert(dr_LastInput[1].HealthDmg) + "   ");
		txt_TopRight[11].setString("Last 3     "
			+ StringConvert(dr_LastInput[2].Hit) + "           "
			+ StringConvert(dr_LastInput[2].Critical) + "                "
			+ StringConvert(dr_LastInput[2].TotalDmg) + "                "
			+ StringConvert(dr_LastInput[2].ShieldDmg) + "                 "
			+ StringConvert(dr_LastInput[2].HealthDmg) + "   ");
		txt_TopRight[12].setString("Last 4     "
			+ StringConvert(dr_LastInput[3].Hit) + "           "
			+ StringConvert(dr_LastInput[3].Critical) + "                "
			+ StringConvert(dr_LastInput[3].TotalDmg) + "                "
			+ StringConvert(dr_LastInput[3].ShieldDmg) + "                 "
			+ StringConvert(dr_LastInput[3].HealthDmg) + "   ");
		txt_TopRight[13].setString("Last 5     "
			+ StringConvert(dr_LastInput[4].Hit) + "           "
			+ StringConvert(dr_LastInput[4].Critical) + "                "
			+ StringConvert(dr_LastInput[4].TotalDmg) + "                "
			+ StringConvert(dr_LastInput[4].ShieldDmg) + "                 "
			+ StringConvert(dr_LastInput[4].HealthDmg) + "   ");

		{
			txt_TopRight[7].setCharacterSize(20);
			txt_TopRight[8].setCharacterSize(20);
			txt_TopRight[9].setCharacterSize(20);
			txt_TopRight[10].setCharacterSize(20);
			txt_TopRight[11].setCharacterSize(20);
			txt_TopRight[12].setCharacterSize(20);
			txt_TopRight[13].setCharacterSize(20);

			txt_TopRight[7].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[8].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[9].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[10].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[11].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[12].setFillColor(sf::Color(255, 0, 0));
			txt_TopRight[13].setFillColor(sf::Color(255, 0, 0));

			vec_BasePositionTR[7].x = 0;
			vec_BasePositionTR[7].y = 224;
			vec_BasePositionTR[8].x = 0;
			vec_BasePositionTR[8].y = 248;
			vec_BasePositionTR[9].x = 0;
			vec_BasePositionTR[9].y = 272;
			vec_BasePositionTR[10].x = 0;
			vec_BasePositionTR[10].y = 296;
			vec_BasePositionTR[11].x = 0;
			vec_BasePositionTR[11].y = 320;
			vec_BasePositionTR[12].x = 0;
			vec_BasePositionTR[12].y = 344;
			vec_BasePositionTR[13].x = 0;
			vec_BasePositionTR[13].y = 368;
		}
		
		for (int count = 14; count < 20; count++)
		{
			txt_TopRight[count].setString("");
			txt_TopRight[count].setCharacterSize(0);
			txt_TopRight[count].setFillColor(sf::Color(0, 0, 0));
			vec_BasePositionTR[count].x = 0;
			vec_BasePositionTR[count].y = 0;
		}

		break;
	}

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

void HUD::CheckMinMax(sf::Vector2f position, sf::Vector2f velocity)
{
	if (position.x < flo_MinX)
	{
		flo_MinX = position.x;
	}

	if (position.x > flo_MaxX)
	{
		flo_MaxX = position.x;
	}

	if (position.y < flo_MinY)
	{
		flo_MinY = position.y;
	}

	if (position.y > flo_MaxY)
	{
		flo_MaxY = position.y;
	}


	if (velocity.x < flo_MinVelX)
	{
		flo_MinVelX = velocity.x;
	}

	if (velocity.x > flo_MaxVelX)
	{
		flo_MaxVelX = velocity.x;
	}

	if (velocity.y < flo_MinVelY)
	{
		flo_MinVelY = velocity.y;
	}

	if (velocity.y > flo_MaxVelY)
	{
		flo_MaxVelY = velocity.y;
	}
}

void HUD::ResetMinMax(sf::Vector2f position, sf::Vector2f velocity)
{
	flo_MinX = position.x;
	flo_MaxX = position.x;
	flo_MinY = position.y;
	flo_MaxY = position.y;

	flo_MinVelX = 0;
	flo_MinVelY = 0;
	flo_MaxVelX = 0;
	flo_MaxVelY = 0;
}

void HUD::UpdateReports(bool type, DamageReport _new)
{
	switch (type)
	{
	case OUTPUT:
		dr_LastOutput[4] = dr_LastOutput[3];
		dr_LastOutput[3] = dr_LastOutput[2];
		dr_LastOutput[2] = dr_LastOutput[1];
		dr_LastOutput[1] = dr_LastOutput[0];
		dr_LastOutput[0] = _new;
		break;
	case INPUT:
		dr_LastInput[4] = dr_LastInput[3];
		dr_LastInput[3] = dr_LastInput[2];
		dr_LastInput[2] = dr_LastInput[1];
		dr_LastInput[1] = dr_LastInput[0];
		dr_LastInput[0] = _new;
	}

	
}