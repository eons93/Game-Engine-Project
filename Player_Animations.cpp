#include "stdafx.h"
#include "Player.h"
#include <iostream>

void Player::loadAnimations()
{
	//Idle Animation
	{
		idle.counter = 0;
		idle.reset = 60;
		idle.frame1Marker = 15;
		idle.frame2Marker = 30;
		idle.frame3Marker = 45;
		idle.frame4Marker = 60;
		if (!idle.source.loadFromFile("Sprites/Player Character/Player_Idle.png"))
		{
			std::cout << "Idle source Failed to Load" << std::endl;
		}

		idle.frame1.left = 0;
		idle.frame1.top = 0;
		idle.frame1.height = 64;
		idle.frame1.width = 64;

		idle.frame2.left = 64;
		idle.frame2.top = 0;
		idle.frame2.height = 64;
		idle.frame2.width = 64;

		idle.frame3.left = 128;
		idle.frame3.top = 0;
		idle.frame3.height = 64;
		idle.frame3.width = 64;

		idle.frame4.left = 192;
		idle.frame4.top = 0;
		idle.frame4.height = 64;
		idle.frame4.width = 64;
	}

	//Run Animation
	{
		run.counter = 0;
		run.reset = 60;
		run.frame1Marker = 15;
		run.frame2Marker = 30;
		run.frame3Marker = 45;
		run.frame4Marker = 60;
		if (!run.source.loadFromFile("Sprites/Player Character/Player_Run.png"))
		{
			std::cout << "Run source Failed to Load" << std::endl;
		}

		run.frame1.left = 0;
		run.frame1.top = 0;
		run.frame1.height = 64;
		run.frame1.width = 64;

		run.frame2.left = 64;
		run.frame2.top = 0;
		run.frame2.height = 64;
		run.frame2.width = 64;

		run.frame3.left = 128;
		run.frame3.top = 0;
		run.frame3.height = 64;
		run.frame3.width = 64;

		run.frame4.left = 192;
		run.frame4.top = 0;
		run.frame4.height = 64;
		run.frame4.width = 64;
	}

	//Jump Animation
	{
		jump.counter = 0;
		jump.reset = 60;
		jump.frame1Marker = 15;
		jump.frame2Marker = 30;
		jump.frame3Marker = 45;
		jump.frame4Marker = 60;
		if (!jump.source.loadFromFile("Sprites/Player Character/Player_Jump.png"))
		{
			std::cout << "Jump source Failed to Load" << std::endl;
		}

		jump.frame1.left = 0;
		jump.frame1.top = 0;
		jump.frame1.height = 64;
		jump.frame1.width = 64;

		jump.frame2.left = 64;
		jump.frame2.top = 0;
		jump.frame2.height = 64;
		jump.frame2.width = 64;

		jump.frame3.left = 128;
		jump.frame3.top = 0;
		jump.frame3.height = 64;
		jump.frame3.width = 64;

		jump.frame4.left = 192;
		jump.frame4.top = 0;
		jump.frame4.height = 64;
		jump.frame4.width = 64;
	}

	//Fall Animation
	{
		fall.counter = 0;
		fall.reset = 60;
		fall.frame1Marker = 15;
		fall.frame2Marker = 30;
		fall.frame3Marker = 45;
		fall.frame4Marker = 60;
		if (!fall.source.loadFromFile("Sprites/Player Character/Player_Fall.png"))
		{
			std::cout << "Fall source Failed to Load" << std::endl;
		}

		fall.frame1.left = 0;
		fall.frame1.top = 0;
		fall.frame1.height = 64;
		fall.frame1.width = 64;

		fall.frame2.left = 0;
		fall.frame2.top = 0;
		fall.frame2.height = 64;
		fall.frame2.width = 64;

		fall.frame3.left = 0;
		fall.frame3.top = 0;
		fall.frame3.height = 64;
		fall.frame3.width = 64;

		fall.frame4.left = 0;
		fall.frame4.top = 0;
		fall.frame4.height = 64;
		fall.frame4.width = 64;
	}

	//Roll Animation
	{
		roll.counter = 0;
		roll.reset = 60;
		roll.frame1Marker = 15;
		roll.frame2Marker = 30;
		roll.frame3Marker = 45;
		roll.frame4Marker = 60;
		if (!roll.source.loadFromFile("Sprites/Player Character/Player_Roll.png"))
		{
			std::cout << "Roll source Failed to Load" << std::endl;
		}

		roll.frame1.left = 0;
		roll.frame1.top = 0;
		roll.frame1.height = 64;
		roll.frame1.width = 64;

		roll.frame2.left = 64;
		roll.frame2.top = 0;
		roll.frame2.height = 64;
		roll.frame2.width = 64;

		roll.frame3.left = 128;
		roll.frame3.top = 0;
		roll.frame3.height = 64;
		roll.frame3.width = 64;

		roll.frame4.left = 192;
		roll.frame4.top = 0;
		roll.frame4.height = 64;
		roll.frame4.width = 64;
	}

	//Duck Animation
	{
		duck.counter = 0;
		duck.reset = 60;
		duck.frame1Marker = 15;
		duck.frame2Marker = 30;
		duck.frame3Marker = 45;
		duck.frame4Marker = 60;
		if (!duck.source.loadFromFile("Sprites/Player Character/Player_Duck.png"))
		{
			std::cout << "Duck source Failed to Load" << std::endl;
		}

		duck.frame1.left = 0;
		duck.frame1.top = 0;
		duck.frame1.height = 64;
		duck.frame1.width = 64;

		duck.frame2.left = 0;
		duck.frame2.top = 0;
		duck.frame2.height = 64;
		duck.frame2.width = 64;

		duck.frame3.left = 0;
		duck.frame3.top = 0;
		duck.frame3.height = 64;
		duck.frame3.width = 64;

		duck.frame4.left = 0;
		duck.frame4.top = 0;
		duck.frame4.height = 64;
		duck.frame4.width = 64;
	}
}