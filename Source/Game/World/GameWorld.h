#pragma once

#include "Engine/World/WorldManager.h"
#include "Game/World/Planet.h"

namespace Game
{
	class Player;
	class GameWorld : public Engine::World
	{
	public:
		void SetCurrentPlayer(Player* player);
		virtual void Update() override;
		virtual std::list<Renderer::Model*>* GetModels() override { return m_CurrentPlanet.GetModels(); };
		virtual std::vector<Renderer::Light>* GetLights() override { return m_CurrentPlanet.GetLights(); };

	private:
		Player* m_Player;
		Planet m_CurrentPlanet;
	};
}
