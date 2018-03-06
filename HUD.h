#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

class HUD
{

private:
	



public:
	HUD();

	sf::Font fon_HUD_Font;
	sf::Text txt_TopLeft[20];
	sf::Text txt_TopRight[20];

	sf::Vector2f vec_BasePositionTL[20];
	sf::Vector2f vec_BasePositionTR[20];

	sf::Vector2f vec_TruePositionTL[20];
	sf::Vector2f vec_TruePositionTR[20];

	// Values captured from attached camera
	float flo_Top;
	float flo_Bottom;
	float flo_Right;
	float flo_Left;

	// Keeps HUD working
	void AttachCamera(sf::View camera);
	void UpdateHUD(Player HUDplayer);
};