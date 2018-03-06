#include "GameWorld.h"

#include "Game/Player/Player.h"

namespace Game
{
	void GameWorld::SetCurrentPlayer(Player * player)
	{
		m_Player = player;
		m_Camera = m_Player->GetCamera();
	}

	void GameWorld::Update()
	{
		m_Player->Update();

		m_CurrentPlanet.Update();
	}
}
