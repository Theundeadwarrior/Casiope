#include "GameWorld.h"

#include "Game/Player/Player.h"

namespace Game
{
	GameWorld::GameWorld()
	{
		auto* mbdb = BlockDataBase::CreateInstance();
		mbdb->LoadBlockDataBase("blocks.data");
		m_CurrentPlanet = new Planet(PlanetParameters());
	}

	void GameWorld::SetCurrentPlayer(Player * player)
	{
		m_Player = player;
		m_Camera = m_Player->GetCamera();
	}

	void GameWorld::Update()
	{
		m_Player->Update();

		if (m_CurrentPlanet != nullptr)
		{
			m_CurrentPlanet->Update(m_Player->GetPosition());
		}
	}

	std::list<Renderer::Model*>* GameWorld::GetModels() 
	{ 
		return m_CurrentPlanet->GetModels(); 
	}

	std::vector<Renderer::Light>* GameWorld::GetLights() 
	{ 
		return m_CurrentPlanet->GetLights(); 
	}
	Renderer::Model * GameWorld::GetSkyBox()
	{
		return m_CurrentPlanet->GetSkyBox();;
	}
}
