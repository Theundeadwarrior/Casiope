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
	private:
		Renderer::SkyBox m_SkyBox;
		Camera* m_Camera; // todo: Move this to a player class!! We could have multiple players!
	};


	class WorldManager
	{
	public:
		WorldManager();
		~WorldManager();


		void SetCurrentWorld(World* world)
		{
			m_CurrentWorld = world;
		}

		void Update();
	private:
		World* m_CurrentWorld;
	};
}
