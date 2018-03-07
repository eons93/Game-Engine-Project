#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"
#include "Engine.h"


void Engine::LoadAnimations()
{
	//Elite Animations
	{
		ani_EliteIdle.InitializeAnimation(4, 60);
		if (!ani_EliteIdle.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Idle_B.png"))
		{
			std::cout << "Idle source Failed to Load for Elite" << std::endl;
		}

		ani_EliteFall.InitializeAnimation(1, 60);
		if (!ani_EliteFall.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Fall_B.png"))
		{
			std::cout << "Fall source Failed to Load for Elite" << std::endl;
		}

		ani_EliteRun.InitializeAnimation(4, 60);
		if (!ani_EliteRun.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Run_B.png"))
		{
			std::cout << "Run source Failed to Load for Elite" << std::endl;
		}
	}

	//Grunt Animations
	{
		ani_GruntIdle.InitializeAnimation(4, 60);
		if (!ani_GruntIdle.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Idle_A.png"))
		{
			std::cout << "Idle source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntFall.InitializeAnimation(1, 60);
		if (!ani_GruntFall.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Fall_A.png"))
		{
			std::cout << "Fall source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntRun.InitializeAnimation(4, 60);
		if (!ani_GruntRun.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Run_A.png"))
		{
			std::cout << "Run source Failed to Load for Grunt" << std::endl;
		}
	}

	
}