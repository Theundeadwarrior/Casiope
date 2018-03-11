#pragma once

#include "Engine/World/World.h"
#include "Game/World/Planet.h"

namespace Game
{
	class Player;
	class GameWorld : public Engine::World
	{
	public:
		GameWorld();

		void SetCurrentPlayer(Player* player);
		virtual void Update() override;
		virtual std::list<Renderer::Model*>* GetModels() override;
		virtual std::vector<Renderer::Light>* GetLights() override;
		virtual Renderer::Model* GetSkyBox() override;

	private:
		Player* m_Player;
		Planet* m_CurrentPlanet;
	};
}
