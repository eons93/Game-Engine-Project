#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Animation
{

private:
	

public:
	Animation();

	// Image holding the frames
	sf::Texture txu_Source;
	
	// Sets Area of attached texture to be drawn
	sf::IntRect rec_Frame1;		
	sf::IntRect rec_Frame2;
	sf::IntRect rec_Frame3;
	sf::IntRect rec_Frame4;

	// Manages how animation runs
	int int_Counter;			// keeps track of where the animation is
	int int_ResetValue;				// how long animation runs for in frames.

	int int_Frame_Marker1;		// last frame that frame1 is used.
	int int_Frame_Marker2;		// last frame that frame2 is used.
	int int_Frame_Marker3;		// last frame that frame3 is used.
	int int_Frame_Marker4;		// last frame that frame4 is used.

	// Returns what frame to draw
	sf::IntRect Animate();
};