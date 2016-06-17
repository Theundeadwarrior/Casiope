#pragma once

#include "Renderer\GraphicsEngine.h"

namespace Engine
{
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void Initialize();
		void Shutdown();

		int Loop();

	private:
		GraphicsEngine m_Renderer;
	};

}

