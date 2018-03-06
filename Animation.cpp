#include "stdafx.h"
#include "Animation.h"
#include <iostream>


Animation::Animation()
{
	
}

// Based on animation manipulation stats, returns frame desired.
sf::IntRect Animation::Animate()
{
	// while the animation counter reaches certain values, 
	// return the proper frame and increase counter
	while (int_Counter < int_Frame_Marker1)
	{
		int_Counter++;
		return rec_Frame1;
	}
	while (int_Counter < int_Frame_Marker2)
	{
		int_Counter++;
		return rec_Frame2;
	}
	while (int_Counter < int_Frame_Marker3)
	{
		int_Counter++;
		return rec_Frame3;
	}
	while (int_Counter < int_Frame_Marker4)
	{
		int_Counter++;
		return rec_Frame4;
	}

	// When animation is over, reset.
	if (int_Counter == int_ResetValue)
	{
		int_Counter = 0;
		return rec_Frame1;
	}
}