#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Animation
{

private:
	

public:
	Animation();

	// Image holding the frames
	sf::Texture source;
	
	// Sets Area of attached texture to be drawn
	sf::IntRect frame1;		
	sf::IntRect frame2;
	sf::IntRect frame3;
	sf::IntRect frame4;

	// Manages how animation runs
	int counter;			// keeps track of where the animation is
	int reset;				// how long animation runs for in frames.

	int frame1Marker;		// last frame that frame1 is used.
	int frame2Marker;		// last frame that frame2 is used.
	int frame3Marker;		// last frame that frame3 is used.
	int frame4Marker;		// last frame that frame4 is used.

	// Returns what frame to draw
	sf::IntRect animate();
};