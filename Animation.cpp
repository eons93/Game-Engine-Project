#include "stdafx.h"
#include "Animation.h"
#include <iostream>


Animation::Animation()
{
	rec_Frame.resize(16);
	int_FrameMarker.resize(16);
}

void Animation::InitializeAnimation(int num_frames, int duration)
{
	int_DurationCounter = 0;
	int_Duration = duration;
	int_FrameCounter = 0;
	int_NumFrames = num_frames;
	int frameLength = duration / num_frames;
	

	int_FrameMarker[0] = frameLength * 1;
	int_FrameMarker[1] = frameLength * 2;
	int_FrameMarker[2] = frameLength * 3;
	int_FrameMarker[3] = frameLength * 4;

	for (int count = 0; count < int_NumFrames; count++)
	{
		rec_Frame[count].left = count * 64;
		rec_Frame[count].top = 0;
		rec_Frame[count].height = 64;
		rec_Frame[count].width = 64;
	}
	
	

}

// Based on animation manipulation stats, returns frame desired.
sf::IntRect Animation::Animate()
{

	if (int_NumFrames == 1)
	{
		while (int_DurationCounter < int_FrameMarker[0])
		{
			int_DurationCounter++;
			return rec_Frame[0];
		}
	}

	if (int_NumFrames == 2)
	{
		while (int_DurationCounter < int_FrameMarker[0])
		{
			int_DurationCounter++;
			return rec_Frame[0];
		}
		while (int_DurationCounter < int_FrameMarker[1])
		{
			int_DurationCounter++;
			return rec_Frame[1];
		}
	}
	
	if (int_NumFrames == 3)
	{
		while (int_DurationCounter < int_FrameMarker[0])
		{
			int_DurationCounter++;
			return rec_Frame[0];
		}
		while (int_DurationCounter < int_FrameMarker[1])
		{
			int_DurationCounter++;
			return rec_Frame[1];
		}
		while (int_DurationCounter < int_FrameMarker[2])
		{
			int_DurationCounter++;
			return rec_Frame[2];
		}
	}

	if (int_NumFrames == 4)
	{
		while (int_DurationCounter < int_FrameMarker[0])
		{
			int_DurationCounter++;
			return rec_Frame[0];
		}
		while (int_DurationCounter < int_FrameMarker[1])
		{
			int_DurationCounter++;
			return rec_Frame[1];
		}
		while (int_DurationCounter < int_FrameMarker[2])
		{
			int_DurationCounter++;
			return rec_Frame[2];
		}
		while (int_DurationCounter < int_FrameMarker[3])
		{
			int_DurationCounter++;
			return rec_Frame[3];
		}
	}
	
	/*
	while (int_DurationCounter < int_FrameMarker[0])
	{
		int_DurationCounter++;
		return rec_Frame[0];
	}
	while (int_DurationCounter < int_FrameMarker[1])
	{
		int_DurationCounter++;
		return rec_Frame[1];
	}
	while (int_DurationCounter < int_FrameMarker[2])
	{
		int_DurationCounter++;
		return rec_Frame[2];
	}
	while (int_DurationCounter < int_FrameMarker[3])
	{
		int_DurationCounter++;
		return rec_Frame[3];
	}*/

	// When animation is over, reset.
	if (int_DurationCounter == int_Duration)
	{
		int_DurationCounter = 0;
		return rec_Frame[0];
	}
}