#include "stdafx.h"
#include "Engine.h"
#include "Level.h"
#include <iostream>

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	// Draw the Level
	m_Window.draw(level.background);
	m_Window.draw(level.levelStructure);

	
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		m_Window.draw(level.selectedMap.CollisionData[count].collisionArea);
	}
	for (int count = 0; count < MAXSLOPES; count++)
	{
		m_Window.draw(level.selectedMap.SlopeData[count].bottomCollision.collisionArea);
		m_Window.draw(level.selectedMap.SlopeData[count].topCollision.collisionArea);
		m_Window.draw(level.selectedMap.SlopeData[count].leftCollision.collisionArea);
		m_Window.draw(level.selectedMap.SlopeData[count].rightCollision.collisionArea);
	}
	for (int count = 0; count < MAXPLATFORMS; count++)
	{
		m_Window.draw(level.selectedMap.PlatformData[count].platform);
		m_Window.draw(level.selectedMap.PlatformData[count].bottomCollision.collisionArea);
		m_Window.draw(level.selectedMap.PlatformData[count].topCollision.collisionArea);
		m_Window.draw(level.selectedMap.PlatformData[count].leftCollision.collisionArea);
		m_Window.draw(level.selectedMap.PlatformData[count].rightCollision.collisionArea);
	}

	// Draw Player
	m_Window.draw(player.getSprite());
	m_Window.draw(player.hitBox.collisionArea);

	// Draw Enemies


	// Draw HUD
	for (int count = 0; count < 20; count++)
	{
		m_Window.draw(hud.textTL[count]);
		m_Window.draw(hud.textTR[count]);
		m_Window.draw(hud.textBL[count]);
		m_Window.draw(hud.textBR[count]);
	}
	

	// Show everything we have just drawn
	m_Window.display();
}