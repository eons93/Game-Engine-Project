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
		if (!txu_EliteFiring.loadFromFile("Sprites/Enemies/Enemy_Firing_B.png"))   
		{
			std::cout << "Elite Arm: Firing source Failed to Load" << std::endl;
		}
		if (!txu_EliteAiming.loadFromFile("Sprites/Enemies/Enemy_Aiming_B.png"))   
		{
			std::cout << "Elite Arm: Aiming source Failed to Load" << std::endl;
		}
		if (!txu_EliteNoShow.loadFromFile("Sprites/Enemies/Enemy_NoShow_B.png"))   
		{
			std::cout << "Elite Arm: NoShow source Failed to Load" << std::endl;
		}

		ani_EliteIdle.InitializeAnimation(4, 1);
		if (!ani_EliteIdle.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Idle_B.png"))
		{
			std::cout << "Idle source Failed to Load for Elite" << std::endl;
		}

		ani_EliteDeath.InitializeAnimation(4, 1);
		if (!ani_EliteDeath.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Death_B.png"))
		{
			std::cout << "Death source Failed to Load for Elite" << std::endl;
		}

		ani_EliteFall.InitializeAnimation(1, 1);
		if (!ani_EliteFall.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Fall_B.png"))
		{
			std::cout << "Fall source Failed to Load for Elite" << std::endl;
		}

		ani_EliteJump.InitializeAnimation(4, 1);
		if (!ani_EliteJump.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Jump_B.png"))
		{
			std::cout << "Jump source Failed to Load for Elite" << std::endl;
		}

		ani_EliteMelee.InitializeAnimation(4, 1);
		if (!ani_EliteMelee.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Melee_B.png"))
		{
			std::cout << "Melee source Failed to Load for Elite" << std::endl;
		}

		ani_EliteRun.InitializeAnimation(4, 1);
		if (!ani_EliteRun.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Run_B.png"))
		{
			std::cout << "Run source Failed to Load for Elite" << std::endl;
		}

		ani_EliteBlock.InitializeAnimation(1, 1);
		if (!ani_EliteBlock.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Block_B.png"))
		{
			std::cout << "Block source Failed to Load for Elite" << std::endl;
		}

		ani_EliteDuck.InitializeAnimation(1, 1);
		if (!ani_EliteDuck.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Duck_B.png"))
		{
			std::cout << "Duck source Failed to Load for Elite" << std::endl;
		}

		ani_EliteRoll.InitializeAnimation(4, 1);
		if (!ani_EliteRoll.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Roll_B.png"))
		{
			std::cout << "Roll source Failed to Load for Elite" << std::endl;
		}
	}

	//Grunt Animations
	{
		if (!txu_GruntFiring.loadFromFile("Sprites/Enemies/Enemy_Firing_A.png"))   
		{
			std::cout << "Grunt Arm: Firing source Failed to Load" << std::endl;
		}
		if (!txu_GruntAiming.loadFromFile("Sprites/Enemies/Enemy_Aiming_A.png"))  
		{
			std::cout << "Grunt Arm: Aiming source Failed to Load" << std::endl;
		}
		if (!txu_GruntNoShow.loadFromFile("Sprites/Enemies/Enemy_NoShow_A.png"))   
		{
			std::cout << "Grunt Arm: NoShow source Failed to Load" << std::endl;
		}

		ani_GruntIdle.InitializeAnimation(4, 1);
		if (!ani_GruntIdle.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Idle_A.png"))
		{
			std::cout << "Idle source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntDeath.InitializeAnimation(4, 1);
		if (!ani_GruntDeath.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Death_A.png"))
		{
			std::cout << "Death source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntFall.InitializeAnimation(1, 1);
		if (!ani_GruntFall.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Fall_A.png"))
		{
			std::cout << "Fall source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntJump.InitializeAnimation(4, 1);
		if (!ani_GruntJump.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Jump_A.png"))
		{
			std::cout << "Jump source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntMelee.InitializeAnimation(4, 1);
		if (!ani_GruntMelee.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Melee_A.png"))
		{
			std::cout << "Melee source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntRun.InitializeAnimation(4, 1);
		if (!ani_GruntRun.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Run_A.png"))
		{
			std::cout << "Run source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntBlock.InitializeAnimation(1, 1);
		if (!ani_GruntBlock.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Block_A.png"))
		{
			std::cout << "Block source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntDuck.InitializeAnimation(1, 1);
		if (!ani_GruntDuck.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Duck_A.png"))
		{
			std::cout << "Duck source Failed to Load for Grunt" << std::endl;
		}

		ani_GruntRoll.InitializeAnimation(4, 1);
		if (!ani_GruntRoll.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Roll_A.png"))
		{
			std::cout << "Roll source Failed to Load for Grunt" << std::endl;
		}
	}
}