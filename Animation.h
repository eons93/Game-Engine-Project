#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Animation
{

private:
	

public:
	Animation();
	void InitializeAnimation(int num_frames, int duration);

	// Image holding the frames
	sf::Texture txu_Source;
	
	// Sets Area of attached texture to be drawn

	std::vector<sf::IntRect> rec_Frame;
	std::vector<int> int_FrameMarker;
	//sf::IntRect rec_Frame1;		
	//sf::IntRect rec_Frame2;
	//sf::IntRect rec_Frame3;
	//sf::IntRect rec_Frame4;

	// Manages how animation runs
	int int_DurationCounter;			// keeps track of where the animation is
	int int_Duration;			// how long animation runs for in frames.
	int int_NumFrames;
	int int_FrameCounter;
	
	

	//int int_Frame_Marker1;		// last frame that frame1 is used.
	//int int_Frame_Marker2;		// last frame that frame2 is used.
	//int int_Frame_Marker3;		// last frame that frame3 is used.
	//int int_Frame_Marker4;		// last frame that frame4 is used.

	// Returns what frame to draw
	sf::IntRect Animate();
};