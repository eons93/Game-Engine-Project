#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Animation
{

private:
	

public:
	Animation();
	void InitializeAnimation(int num_frames, float duration);

	// Image holding the frames
	sf::Texture txu_Source;
	
	// Sets Area of attached texture to be drawn

	std::vector<sf::IntRect> rec_Frame;
	std::vector<float> flo_FrameMarker;

	// Manages how animation runs
	float flo_DurationCurrent;			// keeps track of where the animation is
	int flo_DurationSeconds;					// how long animation runs for in frames.
	int int_NumFrames;
	int int_FrameCounter;

	// Returns what frame to draw
	sf::IntRect Animate(float ElapsedTime);
};