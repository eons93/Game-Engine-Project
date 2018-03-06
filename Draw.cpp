#include "stdafx.h"
#include "Engine.h"
#include "Enemy.h"
#include <iostream>

void Engine::Draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	// Draw the Level
	m_Window.draw(rs_Background);
	m_Window.draw(spr_LevelStructure);

	
	for (int count = 0; count < MAXCOLLISIONS; count++)
	{
		m_Window.draw(map_Selected.col_CollisionData[count].rs_CollisionArea);
	}
	for (int count = 0; count < MAXSLOPES; count++)
	{
		m_Window.draw(map_Selected.slo_SlopeData[count].col_BottomCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.slo_SlopeData[count].col_TopCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.slo_SlopeData[count].col_LeftCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.slo_SlopeData[count].col_RightCollision.rs_CollisionArea);
	}
	for (int count = 0; count < MAXPLATFORMS; count++)
	{
		m_Window.draw(map_Selected.pla_PlatformData[count].rs_Platform);
		m_Window.draw(map_Selected.pla_PlatformData[count].col_BottomCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.pla_PlatformData[count].col_TopCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.pla_PlatformData[count].col_LeftCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.pla_PlatformData[count].col_RightCollision.rs_CollisionArea);
	}
	
	for (int count = 0; count < MAXENEMIES; count++)
	{
		m_Window.draw(ene_Spawned[count].GetSprite());
		m_Window.draw(ene_Spawned[count].txt_Name);
	}
	

	// Draw Player
	m_Window.draw(player.GetSprite());
	

	
	

	// Draw HUD
	for (int count = 0; count < 20; count++)
	{
		m_Window.draw(hud.txt_TopLeft[count]);
		m_Window.draw(hud.txt_TopRight[count]);
	}

	// Show everything we have just drawn
	m_Window.display();
}