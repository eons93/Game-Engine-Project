#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

class HUD
{

private:
	



public:
	HUD();

	sf::Font font;
	sf::Text textTL[20];
	sf::Text textTR[20];
	sf::Text textBL[20];
	sf::Text textBR[20];

	sf::Vector2f basePositionTL[20];
	sf::Vector2f basePositionTR[20];
	sf::Vector2f basePositionBL[20];
	sf::Vector2f basePositionBR[20];

	sf::Vector2f truePositionTL[20];
	sf::Vector2f truePositionTR[20];
	sf::Vector2f truePositionBL[20];
	sf::Vector2f truePositionBR[20];

	// Values captured from attached camera
	float top;
	float bottom;
	float right;
	float left;

	// Keeps HUD working
	void attachCamera(sf::View camera);
	void updateHUD(Player HUDplayer);
	
	
};