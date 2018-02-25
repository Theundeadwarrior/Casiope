#include "GameWorld.h"

#include "Game/Player/Player.h"

namespace Game
{
	void GameWorld::SetCurrentPlayer(Player * player)
	{
		m_CurrentPlayer = player;
		m_Camera = m_CurrentPlayer->GetCamera();
	}

	void GameWorld::Update()
	{
		m_CurrentPlayer->Update();
		m_MinecraftWorld.Update();
	}
}
