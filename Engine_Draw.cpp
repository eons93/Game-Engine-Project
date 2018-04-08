#include "stdafx.h"
#include "Engine.h"
#include "Enemy.h"
#include <iostream>

void Engine::Draw()
{
	// Rub out the last frame
	m_Window.clear(Color::Black);

	// Draw the Level
	m_Window.draw(rs_Background);
	m_Window.draw(spr_LevelStructure);

	for (int count = 0; count < map_Selected.int_MaxCollisionIndex; count++)
	{
		m_Window.draw(map_Selected.col_CollisionData[map_Selected.int_LoadedCollision[count]].rs_CollisionArea);
	}
	for (int count = 0; count < map_Selected.int_NumSlop; count++)
	{
		m_Window.draw(map_Selected.slo_SlopeData[count].col_BottomCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.slo_SlopeData[count].col_TopCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.slo_SlopeData[count].col_LeftCollision.rs_CollisionArea);
		m_Window.draw(map_Selected.slo_SlopeData[count].col_RightCollision.rs_CollisionArea);
	}
	
	for (int count = 0; count < map_Selected.int_NumPlat; count++)
	{
		m_Window.draw(map_Selected.pla_PlatformData[count].rs_Platform);
	}
	
	for (int count = 0; count < map_Selected.int_MaxEnemyIndex; count++)
	{
		if (ene_Spawned[map_Selected.int_LoadedEnemies[count]].flo_FinalDuration > 0)
		{
			m_Window.draw(ene_Spawned[map_Selected.int_LoadedEnemies[count]].GetSprite());
			m_Window.draw(ene_Spawned[map_Selected.int_LoadedEnemies[count]].GetArm());
			m_Window.draw(ene_Spawned[map_Selected.int_LoadedEnemies[count]].rec_DamageFlasher);
			m_Window.draw(ene_Spawned[map_Selected.int_LoadedEnemies[count]].txt_Name);
			m_Window.draw(ene_Spawned[map_Selected.int_LoadedEnemies[count]].rec_Background);
			m_Window.draw(ene_Spawned[map_Selected.int_LoadedEnemies[count]].rec_CurrentHealth);
			m_Window.draw(ene_Spawned[map_Selected.int_LoadedEnemies[count]].rec_CurrentShields);
		}
	}
	
	// Draw Player
	if (player.GetFinalDuration() > 0)
	{
		m_Window.draw(player.GetSprite());
		m_Window.draw(player.GetArm());
		m_Window.draw(player.GetFlasher());
	}
	else
	{
		m_Window.draw(hud.txt_GameOver);
	}
	

	// Draw HUD
	m_Window.draw(hud.txt_HealthBar);
	m_Window.draw(hud.txt_ShieldsBar);
	m_Window.draw(hud.rec_HealthBG);
	m_Window.draw(hud.rec_ShieldsBG);
	m_Window.draw(hud.rec_HealthBar);
	m_Window.draw(hud.rec_ShieldsBar);

	for (int count = 0; count < 20; count++)
	{
		m_Window.draw(hud.txt_TopLeft[count]);
		m_Window.draw(hud.txt_TopRight[count]);
	}

	// Show everything we have just drawn
	m_Window.display();
}