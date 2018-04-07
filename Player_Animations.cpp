#include "stdafx.h"
#include "Player.h"
#include <iostream>

void Player::LoadAnimations()
{


	if (!txu_Firing.loadFromFile("Sprites/Player Character/Player_Firing.png"))   //**//
	{
		std::cout << "Player Arm: Firing source Failed to Load" << std::endl;
	}
	if (!txu_Aiming.loadFromFile("Sprites/Player Character/Player_Aiming.png"))   //**//
	{
		std::cout << "Player Arm: Aiming source Failed to Load" << std::endl;
	}
	if (!txu_NoShow.loadFromFile("Sprites/Player Character/Player_NoShow.png"))   //**//
	{
		std::cout << "Player Arm: NoShow source Failed to Load" << std::endl;
	}

	//Idle Animation
	{
		ani_Idle.InitializeAnimation(4, 1);
		if (!ani_Idle.txu_Source.loadFromFile("Sprites/Player Character/Player_Idle.png"))
		{
			std::cout << "Idle source Failed to Load" << std::endl;
		}
	}

	//Death Animation
	{
		ani_Death.InitializeAnimation(4, 1);
		if (!ani_Death.txu_Source.loadFromFile("Sprites/Player Character/Player_Death.png"))
		{
			std::cout << "Death source Failed to Load" << std::endl;
		}
	}

	//Run Animation
	{
		ani_Run.InitializeAnimation(4, 1);
		if (!ani_Run.txu_Source.loadFromFile("Sprites/Player Character/Player_Run.png"))
		{
			std::cout << "Run source Failed to Load" << std::endl;
		}
	}

	//Jump Animation
	{
		ani_Jump.InitializeAnimation(4, .75);
		if (!ani_Jump.txu_Source.loadFromFile("Sprites/Player Character/Player_Jump.png"))
		{
			std::cout << "Jump source Failed to Load" << std::endl;
		}
	}

	//Fall Animation
	{
		ani_Fall.InitializeAnimation(1, 1);
		if (!ani_Fall.txu_Source.loadFromFile("Sprites/Player Character/Player_Fall.png"))
		{
			std::cout << "Fall source Failed to Load" << std::endl;
		}
	}

	//Roll Animation
	{
		ani_Roll.InitializeAnimation(4, 1);
		if (!ani_Roll.txu_Source.loadFromFile("Sprites/Player Character/Player_Roll.png"))
		{
			std::cout << "Roll source Failed to Load" << std::endl;
		}
	}

	//Duck Animation
	{
		ani_Duck.InitializeAnimation(1, 1);
		if (!ani_Duck.txu_Source.loadFromFile("Sprites/Player Character/Player_Duck.png"))
		{
			std::cout << "Duck source Failed to Load" << std::endl;
		}
	}

	//Block Animation
	{
		ani_Block.InitializeAnimation(1, 1);
		if (!ani_Block.txu_Source.loadFromFile("Sprites/Player Character/Player_Block.png"))
		{
			std::cout << "Block source Failed to Load" << std::endl;
		}
	}

	//Range Attack (ground)
	{
		ani_Shoot.InitializeAnimation(4, 1);
		if (!ani_Shoot.txu_Source.loadFromFile("Sprites/Player Character/Player_Shoot_Ground.png"))
		{
			std::cout << "Shoot(ground) source Failed to Load" << std::endl;
		}
	}

	//Range Attack (Air)
	{
		ani_AirShoot.InitializeAnimation(4, 1);
		if (!ani_AirShoot.txu_Source.loadFromFile("Sprites/Player Character/Player_Shoot_Air.png"))
		{
			std::cout << "Shoot(air) source Failed to Load" << std::endl;
		}
	}

	//Melee Attack (ground)
	{
		ani_Melee.InitializeAnimation(4, 1);
		if (!ani_Melee.txu_Source.loadFromFile("Sprites/Player Character/Player_Melee_Ground.png"))
		{
			std::cout << "Melee(ground) source Failed to Load" << std::endl;
		}
	}

	//Melee Attack (air)
	{
		ani_AirMelee.InitializeAnimation(4, 1);
		if (!ani_AirMelee.txu_Source.loadFromFile("Sprites/Player Character/Player_Melee_Air.png"))
		{
			std::cout << "Melee(air) source Failed to Load" << std::endl;
		}
	}
}