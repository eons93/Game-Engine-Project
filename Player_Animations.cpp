#include "stdafx.h"
#include "Player.h"
#include <iostream>

void Player::LoadAnimations()
{
	//Idle Animation
	{
		ani_Idle.int_Counter = 0;
		ani_Idle.int_ResetValue = 60;
		ani_Idle.int_Frame_Marker1 = 15;
		ani_Idle.int_Frame_Marker2 = 30;
		ani_Idle.int_Frame_Marker3 = 45;
		ani_Idle.int_Frame_Marker4 = 60;
		if (!ani_Idle.txu_Source.loadFromFile("Sprites/Player Character/Player_Idle.png"))
		{
			std::cout << "Idle source Failed to Load" << std::endl;
		}

		ani_Idle.rec_Frame1.left = 0;
		ani_Idle.rec_Frame1.top = 0;
		ani_Idle.rec_Frame1.height = 64;
		ani_Idle.rec_Frame1.width = 64;

		ani_Idle.rec_Frame2.left = 64;
		ani_Idle.rec_Frame2.top = 0;
		ani_Idle.rec_Frame2.height = 64;
		ani_Idle.rec_Frame2.width = 64;

		ani_Idle.rec_Frame3.left = 128;
		ani_Idle.rec_Frame3.top = 0;
		ani_Idle.rec_Frame3.height = 64;
		ani_Idle.rec_Frame3.width = 64;

		ani_Idle.rec_Frame4.left = 192;
		ani_Idle.rec_Frame4.top = 0;
		ani_Idle.rec_Frame4.height = 64;
		ani_Idle.rec_Frame4.width = 64;
	}

	//Run Animation
	{
		ani_Run.int_Counter = 0;
		ani_Run.int_ResetValue = 60;
		ani_Run.int_Frame_Marker1 = 15;
		ani_Run.int_Frame_Marker2 = 30;
		ani_Run.int_Frame_Marker3 = 45;
		ani_Run.int_Frame_Marker4 = 60;
		if (!ani_Run.txu_Source.loadFromFile("Sprites/Player Character/Player_Run.png"))
		{
			std::cout << "Run source Failed to Load" << std::endl;
		}

		ani_Run.rec_Frame1.left = 0;
		ani_Run.rec_Frame1.top = 0;
		ani_Run.rec_Frame1.height = 64;
		ani_Run.rec_Frame1.width = 64;

		ani_Run.rec_Frame2.left = 64;
		ani_Run.rec_Frame2.top = 0;
		ani_Run.rec_Frame2.height = 64;
		ani_Run.rec_Frame2.width = 64;

		ani_Run.rec_Frame3.left = 128;
		ani_Run.rec_Frame3.top = 0;
		ani_Run.rec_Frame3.height = 64;
		ani_Run.rec_Frame3.width = 64;

		ani_Run.rec_Frame4.left = 192;
		ani_Run.rec_Frame4.top = 0;
		ani_Run.rec_Frame4.height = 64;
		ani_Run.rec_Frame4.width = 64;
	}

	//Jump Animation
	{
		ani_Jump.int_Counter = 0;
		ani_Jump.int_ResetValue = 60;
		ani_Jump.int_Frame_Marker1 = 15;
		ani_Jump.int_Frame_Marker2 = 30;
		ani_Jump.int_Frame_Marker3 = 45;
		ani_Jump.int_Frame_Marker4 = 60;
		if (!ani_Jump.txu_Source.loadFromFile("Sprites/Player Character/Player_Jump.png"))
		{
			std::cout << "Jump source Failed to Load" << std::endl;
		}

		ani_Jump.rec_Frame1.left = 0;
		ani_Jump.rec_Frame1.top = 0;
		ani_Jump.rec_Frame1.height = 64;
		ani_Jump.rec_Frame1.width = 64;

		ani_Jump.rec_Frame2.left = 64;
		ani_Jump.rec_Frame2.top = 0;
		ani_Jump.rec_Frame2.height = 64;
		ani_Jump.rec_Frame2.width = 64;

		ani_Jump.rec_Frame3.left = 128;
		ani_Jump.rec_Frame3.top = 0;
		ani_Jump.rec_Frame3.height = 64;
		ani_Jump.rec_Frame3.width = 64;

		ani_Jump.rec_Frame4.left = 192;
		ani_Jump.rec_Frame4.top = 0;
		ani_Jump.rec_Frame4.height = 64;
		ani_Jump.rec_Frame4.width = 64;
	}

	//Fall Animation
	{
		ani_Fall.int_Counter = 0;
		ani_Fall.int_ResetValue = 60;
		ani_Fall.int_Frame_Marker1 = 15;
		ani_Fall.int_Frame_Marker2 = 30;
		ani_Fall.int_Frame_Marker3 = 45;
		ani_Fall.int_Frame_Marker4 = 60;
		if (!ani_Fall.txu_Source.loadFromFile("Sprites/Player Character/Player_Fall.png"))
		{
			std::cout << "Fall source Failed to Load" << std::endl;
		}

		ani_Fall.rec_Frame1.left = 0;
		ani_Fall.rec_Frame1.top = 0;
		ani_Fall.rec_Frame1.height = 64;
		ani_Fall.rec_Frame1.width = 64;

		ani_Fall.rec_Frame2.left = 0;
		ani_Fall.rec_Frame2.top = 0;
		ani_Fall.rec_Frame2.height = 64;
		ani_Fall.rec_Frame2.width = 64;

		ani_Fall.rec_Frame3.left = 0;
		ani_Fall.rec_Frame3.top = 0;
		ani_Fall.rec_Frame3.height = 64;
		ani_Fall.rec_Frame3.width = 64;

		ani_Fall.rec_Frame4.left = 0;
		ani_Fall.rec_Frame4.top = 0;
		ani_Fall.rec_Frame4.height = 64;
		ani_Fall.rec_Frame4.width = 64;
	}

	//Roll Animation
	{
		ani_Roll.int_Counter = 0;
		ani_Roll.int_ResetValue = 60;
		ani_Roll.int_Frame_Marker1 = 15;
		ani_Roll.int_Frame_Marker2 = 30;
		ani_Roll.int_Frame_Marker3 = 45;
		ani_Roll.int_Frame_Marker4 = 60;
		if (!ani_Roll.txu_Source.loadFromFile("Sprites/Player Character/Player_Roll.png"))
		{
			std::cout << "Roll source Failed to Load" << std::endl;
		}

		ani_Roll.rec_Frame1.left = 0;
		ani_Roll.rec_Frame1.top = 0;
		ani_Roll.rec_Frame1.height = 64;
		ani_Roll.rec_Frame1.width = 64;

		ani_Roll.rec_Frame2.left = 64;
		ani_Roll.rec_Frame2.top = 0;
		ani_Roll.rec_Frame2.height = 64;
		ani_Roll.rec_Frame2.width = 64;

		ani_Roll.rec_Frame3.left = 128;
		ani_Roll.rec_Frame3.top = 0;
		ani_Roll.rec_Frame3.height = 64;
		ani_Roll.rec_Frame3.width = 64;

		ani_Roll.rec_Frame4.left = 192;
		ani_Roll.rec_Frame4.top = 0;
		ani_Roll.rec_Frame4.height = 64;
		ani_Roll.rec_Frame4.width = 64;
	}

	//Duck Animation
	{
		ani_Duck.int_Counter = 0;
		ani_Duck.int_ResetValue = 60;
		ani_Duck.int_Frame_Marker1 = 15;
		ani_Duck.int_Frame_Marker2 = 30;
		ani_Duck.int_Frame_Marker3 = 45;
		ani_Duck.int_Frame_Marker4 = 60;
		if (!ani_Duck.txu_Source.loadFromFile("Sprites/Player Character/Player_Duck.png"))
		{
			std::cout << "Duck source Failed to Load" << std::endl;
		}

		ani_Duck.rec_Frame1.left = 0;
		ani_Duck.rec_Frame1.top = 0;
		ani_Duck.rec_Frame1.height = 64;
		ani_Duck.rec_Frame1.width = 64;

		ani_Duck.rec_Frame2.left = 0;
		ani_Duck.rec_Frame2.top = 0;
		ani_Duck.rec_Frame2.height = 64;
		ani_Duck.rec_Frame2.width = 64;

		ani_Duck.rec_Frame3.left = 0;
		ani_Duck.rec_Frame3.top = 0;
		ani_Duck.rec_Frame3.height = 64;
		ani_Duck.rec_Frame3.width = 64;

		ani_Duck.rec_Frame4.left = 0;
		ani_Duck.rec_Frame4.top = 0;
		ani_Duck.rec_Frame4.height = 64;
		ani_Duck.rec_Frame4.width = 64;
	}
}