#pragma once

#include "Renderer\SkyBox\SkyBox.h"

namespace Engine
{
	class World
	{
	public:
		void Update();
	private:
		Renderer::SkyBox m_SkyBox;
	};


	class WorldManager
	{
	public:
		WorldManager();
		~WorldManager();

		void Update();
	private:
		World* m_CurrentWorld;
	};
}
