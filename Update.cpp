#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>

using namespace sf;

void Engine::update()
{
	

	// Apply changes from input
	player.updateStage1();
	
	// Detect Collision
	level.detectCollision1(player);


	// Update Player and Camera
	player.updateStage2();
	updateCamera();
	hud.attachCamera(playerCamera);
	hud.updateHUD(player);
}