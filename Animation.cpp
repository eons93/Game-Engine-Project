#include "stdafx.h"
#include "Animation.h"
#include <iostream>


Animation::Animation()
{
	rec_Frame.resize(16);
	flo_FrameMarker.resize(16);
}

void Animation::InitializeAnimation(int num_frames, float durationSeconds)
{
	flo_DurationCurrent = 0;
	flo_DurationSeconds = durationSeconds;
	int_FrameCounter = 0;
	int_NumFrames = num_frames;
	float frameLength = durationSeconds / num_frames;
	

	flo_FrameMarker[0] = frameLength * 1;
	flo_FrameMarker[1] = frameLength * 2;
	flo_FrameMarker[2] = frameLength * 3;
	flo_FrameMarker[3] = frameLength * 4;

	for (int count = 0; count < int_NumFrames; count++)
	{
		rec_Frame[count].left = count * 64;
		rec_Frame[count].top = 0;
		rec_Frame[count].height = 64;
		rec_Frame[count].width = 64;
	}
	
	

}

// Based on animation manipulation stats, returns frame desired.
sf::IntRect Animation::Animate(float ElapsedTime)
{

	if (int_NumFrames == 1)
	{
		while (flo_DurationCurrent < flo_FrameMarker[0])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[0];
		}
	}

	if (int_NumFrames == 2)
	{
		while (flo_DurationCurrent < flo_FrameMarker[0])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[0];
		}
		while (flo_DurationCurrent < flo_FrameMarker[1])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[1];
		}
	}
	
	if (int_NumFrames == 3)
	{
		while (flo_DurationCurrent < flo_FrameMarker[0])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[0];
		}
		while (flo_DurationCurrent < flo_FrameMarker[1])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[1];
		}
		while (flo_DurationCurrent < flo_FrameMarker[2])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[2];
		}
	}

	if (int_NumFrames == 4)
	{
		while (flo_DurationCurrent < flo_FrameMarker[0])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[0];
		}
		while (flo_DurationCurrent < flo_FrameMarker[1])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[1];
		}
		while (flo_DurationCurrent < flo_FrameMarker[2])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[2];
		}
		while (flo_DurationCurrent < flo_FrameMarker[3])
		{
			flo_DurationCurrent += ElapsedTime;
			return rec_Frame[3];
		}
	}

	// When animation is over, reset.
	if (flo_DurationCurrent >= flo_DurationSeconds)
	{
		flo_DurationCurrent = 0;
		return rec_Frame[0];
	}
}