#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include <iostream>
#include "Enemy.h"

using namespace sf;

void Engine::update()
{
	

	// Apply changes from input
	player.updateStage1();

	
	// Detect Collision
	level.detectCollisionPlayer(player);
	level.detectCollisionEnemy(enemy);
	
	enemy.Update();

	// Update Player and Camera
	player.updateStage2();
	
	updateCamera();
	hud.attachCamera(playerCamera);
	hud.updateHUD(player);
}