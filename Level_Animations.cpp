#include "stdafx.h"
#include "Level.h"
#include "Map.h"
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Enumerations.h"
#include "GeneralFunctions.h"
#include "Enemy.h"


void Level::loadAnimations()
{
	//Idle Animation
	{
		grunt_idle.counter = 0;
		grunt_idle.reset = 60;
		grunt_idle.frame1Marker = 15;
		grunt_idle.frame2Marker = 30;
		grunt_idle.frame3Marker = 45;
		grunt_idle.frame4Marker = 60;
		if (!grunt_idle.source.loadFromFile("Sprites/Enemies/Enemy_Idle.png"))
		{
			std::cout << "Idle source Failed to Load" << std::endl;
		}

		grunt_idle.frame1.left = 0;
		grunt_idle.frame1.top = 0;
		grunt_idle.frame1.height = 64;
		grunt_idle.frame1.width = 64;

		grunt_idle.frame2.left = 64;
		grunt_idle.frame2.top = 0;
		grunt_idle.frame2.height = 64;
		grunt_idle.frame2.width = 64;

		grunt_idle.frame3.left = 128;
		grunt_idle.frame3.top = 0;
		grunt_idle.frame3.height = 64;
		grunt_idle.frame3.width = 64;

		grunt_idle.frame4.left = 192;
		grunt_idle.frame4.top = 0;
		grunt_idle.frame4.height = 64;
		grunt_idle.frame4.width = 64;
	}

	{
		grunt_fall.counter = 0;
		grunt_fall.reset = 60;
		grunt_fall.frame1Marker = 15;
		grunt_fall.frame2Marker = 30;
		grunt_fall.frame3Marker = 45;
		grunt_fall.frame4Marker = 60;
		if (!grunt_fall.source.loadFromFile("Sprites/Player Character/Player_Fall.png"))
		{
			std::cout << "Fall source Failed to Load" << std::endl;
		}

		grunt_fall.frame1.left = 0;
		grunt_fall.frame1.top = 0;
		grunt_fall.frame1.height = 64;
		grunt_fall.frame1.width = 64;

		grunt_fall.frame2.left = 0;
		grunt_fall.frame2.top = 0;
		grunt_fall.frame2.height = 64;
		grunt_fall.frame2.width = 64;

		grunt_fall.frame3.left = 0;
		grunt_fall.frame3.top = 0;
		grunt_fall.frame3.height = 64;
		grunt_fall.frame3.width = 64;

		grunt_fall.frame4.left = 0;
		grunt_fall.frame4.top = 0;
		grunt_fall.frame4.height = 64;
		grunt_fall.frame4.width = 64;
	}


}