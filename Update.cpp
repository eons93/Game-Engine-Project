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

	
	for (int count = 0; count < MAXENEMIES; count++)
	{
		level.detectCollisionEnemy(activeEnemy[count]);
		activeEnemy[count].Update();
	}

	activeEnemy[0].velocity.x += 2;
	activeEnemy[1].velocity.x += 2;


	// Update Player and Camera
	player.updateStage2();
	
	updateCamera();
	hud.attachCamera(playerCamera);
	hud.updateHUD(player);
}