#pragma once

#include "Renderer\SkyBox\SkyBox.h"

namespace Engine
{
	class Camera;

	class World
	{
	public:
		World();
		void Update();

		// getters
		Camera* GetCamera() const { return m_Camera; }

	private:
		Renderer::SkyBox m_SkyBox;
		Camera* m_Camera; // todo: Move this to a player class!! We could have multiple players!
	};


	class WorldManager
	{
	public:
		WorldManager();
		~WorldManager();

		World* GetCurrentWorld() const { return m_CurrentWorld; }

		void SetCurrentWorld(World* world)
		{
			m_CurrentWorld = world;
		}

		void Update();
	private:
		World* m_CurrentWorld;
	};
}
