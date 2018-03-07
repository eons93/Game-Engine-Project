#include "stdafx.h"
#include "Player.h"
#include <iostream>

void Player::LoadAnimations()
{
	//Idle Animation
	{
		ani_Idle.InitializeAnimation(4, 60);
		if (!ani_Idle.txu_Source.loadFromFile("Sprites/Player Character/Player_Idle.png"))
		{
			std::cout << "Idle source Failed to Load" << std::endl;
		}
	}

	//Run Animation
	{
		ani_Run.InitializeAnimation(4, 60);
		if (!ani_Run.txu_Source.loadFromFile("Sprites/Player Character/Player_Run.png"))
		{
			std::cout << "Run source Failed to Load" << std::endl;
		}
	}

	//Jump Animation
	{
		ani_Jump.InitializeAnimation(4, 45);
		if (!ani_Jump.txu_Source.loadFromFile("Sprites/Player Character/Player_Jump.png"))
		{
			std::cout << "Jump source Failed to Load" << std::endl;
		}
	}

	//Fall Animation
	{
		ani_Fall.InitializeAnimation(1, 60);
		if (!ani_Fall.txu_Source.loadFromFile("Sprites/Player Character/Player_Fall.png"))
		{
			std::cout << "Fall source Failed to Load" << std::endl;
		}
	}

	//Roll Animation
	{
		ani_Roll.InitializeAnimation(4, 60);
		if (!ani_Roll.txu_Source.loadFromFile("Sprites/Player Character/Player_Roll.png"))
		{
			std::cout << "Roll source Failed to Load" << std::endl;
		}
	}

	//Duck Animation
	{
		ani_Duck.InitializeAnimation(1, 60);
		if (!ani_Duck.txu_Source.loadFromFile("Sprites/Player Character/Player_Duck.png"))
		{
			std::cout << "Duck source Failed to Load" << std::endl;
		}
	}
}