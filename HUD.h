#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

class HUD
{

private:
	



public:
	HUD();

	// Basic Variables
	sf::Font fon_HUD_Font;
	sf::Text txt_TopLeft[20];
	sf::Text txt_TopRight[20];
	sf::Text txt_GameOver;

	sf::Vector2f vec_BasePositionTL[20];
	sf::Vector2f vec_BasePositionTR[20];

	sf::Vector2f vec_TruePositionTL[20];
	sf::Vector2f vec_TruePositionTR[20];

	HudType ht_CurrentMode;


	// Universal Components
	sf::Text txt_HealthBar;
	sf::RectangleShape rec_HealthBar;
	sf::RectangleShape rec_HealthBG;
	
	sf::Text txt_ShieldsBar;
	sf::RectangleShape rec_ShieldsBar;
	sf::RectangleShape rec_ShieldsBG;
	

	// Movement Mode Components
	float flo_MaxX;
	float flo_MaxY;
	float flo_MinX;
	float flo_MinY;
	float flo_MinVelX;
	float flo_MaxVelX;
	float flo_MinVelY;
	float flo_MaxVelY;
	void CheckMinMax(sf::Vector2f position, sf::Vector2f velocity);
	void ResetMinMax(sf::Vector2f position, sf::Vector2f velocity);

	// Combat Mode Components
	void UpdateReports(bool type, DamageReport _new);
	DamageReport dr_LastOutput[5];
	DamageReport dr_LastInput[5];


	// Values captured from attached camera
	float flo_Top;
	float flo_Bottom;
	float flo_Right;
	float flo_Left;
	sf::Vector2f vec_Center;

	// Keeps HUD working
	void AttachCamera(sf::View camera);
	void UpdateHUD(Player HUDplayer);
};