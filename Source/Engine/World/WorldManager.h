#pragma once

#include "Renderer/SkyBox/SkyBox.h"

namespace Engine
{
	class Camera;

	class World
	{
	public:
		World();
		virtual ~World() {};
		void Update();

		// getters
		Camera* GetCamera() const { return m_Camera; }

	protected:
		Camera* m_Camera; // todo: Move this to a player class!! We could have multiple players!

	private:
		Renderer::SkyBox m_SkyBox;
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
