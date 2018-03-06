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
	//Idle Animation
	{
		ani_GruntIdle.int_Counter = 0;
		ani_GruntIdle.int_ResetValue = 60;
		ani_GruntIdle.int_Frame_Marker1 = 15;
		ani_GruntIdle.int_Frame_Marker2 = 30;
		ani_GruntIdle.int_Frame_Marker3 = 45;
		ani_GruntIdle.int_Frame_Marker4 = 60;
		if (!ani_GruntIdle.txu_Source.loadFromFile("Sprites/Enemies/Enemy_Idle.png"))
		{
			std::cout << "Idle source Failed to Load" << std::endl;
		}

		ani_GruntIdle.rec_Frame1.left = 0;
		ani_GruntIdle.rec_Frame1.top = 0;
		ani_GruntIdle.rec_Frame1.height = 64;
		ani_GruntIdle.rec_Frame1.width = 64;

		ani_GruntIdle.rec_Frame2.left = 64;
		ani_GruntIdle.rec_Frame2.top = 0;
		ani_GruntIdle.rec_Frame2.height = 64;
		ani_GruntIdle.rec_Frame2.width = 64;

		ani_GruntIdle.rec_Frame3.left = 128;
		ani_GruntIdle.rec_Frame3.top = 0;
		ani_GruntIdle.rec_Frame3.height = 64;
		ani_GruntIdle.rec_Frame3.width = 64;

		ani_GruntIdle.rec_Frame4.left = 192;
		ani_GruntIdle.rec_Frame4.top = 0;
		ani_GruntIdle.rec_Frame4.height = 64;
		ani_GruntIdle.rec_Frame4.width = 64;
	}

	{
		ani_GruntFall.int_Counter = 0;
		ani_GruntFall.int_ResetValue = 60;
		ani_GruntFall.int_Frame_Marker1 = 15;
		ani_GruntFall.int_Frame_Marker2 = 30;
		ani_GruntFall.int_Frame_Marker3 = 45;
		ani_GruntFall.int_Frame_Marker4 = 60;
		if (!ani_GruntFall.txu_Source.loadFromFile("Sprites/Player Character/Player_Fall.png"))
		{
			std::cout << "Fall source Failed to Load" << std::endl;
		}

		ani_GruntFall.rec_Frame1.left = 0;
		ani_GruntFall.rec_Frame1.top = 0;
		ani_GruntFall.rec_Frame1.height = 64;
		ani_GruntFall.rec_Frame1.width = 64;

		ani_GruntFall.rec_Frame2.left = 0;
		ani_GruntFall.rec_Frame2.top = 0;
		ani_GruntFall.rec_Frame2.height = 64;
		ani_GruntFall.rec_Frame2.width = 64;

		ani_GruntFall.rec_Frame3.left = 0;
		ani_GruntFall.rec_Frame3.top = 0;
		ani_GruntFall.rec_Frame3.height = 64;
		ani_GruntFall.rec_Frame3.width = 64;

		ani_GruntFall.rec_Frame4.left = 0;
		ani_GruntFall.rec_Frame4.top = 0;
		ani_GruntFall.rec_Frame4.height = 64;
		ani_GruntFall.rec_Frame4.width = 64;
	}


}