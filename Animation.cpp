#include "stdafx.h"
#include "Animation.h"
#include <iostream>


Animation::Animation()
{
	
}

// Based on animation manipulation stats, returns frame desired.
sf::IntRect Animation::animate()
{
	// while the animation counter reaches certain values, 
	// return the proper frame and increase counter
	while (counter < frame1Marker)
	{
		counter++;
		return frame1;
	}
	while (counter < frame2Marker)
	{
		counter++;
		return frame2;
	}
	while (counter < frame3Marker)
	{
		counter++;
		return frame3;
	}
	while (counter < frame4Marker)
	{
		counter++;
		return frame4;
	}

	// When animation is over, reset.
	if (counter == reset)
	{
		counter = 0;
		return frame1;
	}
}