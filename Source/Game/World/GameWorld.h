#pragma once

#include <vector>

#include "Renderer/SkyBox/SkyBox.h"

#include "Engine/World/MinecraftWorld.h"
#include "Engine/World/WorldManager.h"

#include "Game/Player/Player.h"


namespace Game
{
	class GameWorld : public Engine::World
	{
	public:
		void SetCurrentPlayer(Player* player);

		virtual void Update() override;

		virtual Renderer::Mesh* GetMesh() override { return m_MinecraftWorld.GetMesh(); };


	private:
		Player* m_CurrentPlayer;
		Engine::MinecraftWorld m_MinecraftWorld;
		Renderer::SkyBox m_SkyBox;
	};
}
