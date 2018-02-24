#pragma once

#include "Renderer/SkyBox/SkyBox.h"
#include "Engine/World/WorldManager.h"
#include "Game/Player/Player.h"
#include "Game/World/MinecraftWorld.h"

namespace Game
{
	class GameWorld : public Engine::World
	{
	public:
		void SetCurrentPlayer(Player* player);
		virtual void Update() override;
		virtual std::list<Renderer::Model*>* GetModels() override { return m_MinecraftWorld.GetModels(); };
		virtual std::vector<Renderer::Light>* GetLights() override { return m_MinecraftWorld.GetLights(); };

	private:
		Player* m_CurrentPlayer;
		MinecraftWorld m_MinecraftWorld;
		Renderer::SkyBox m_SkyBox;
	};
}
