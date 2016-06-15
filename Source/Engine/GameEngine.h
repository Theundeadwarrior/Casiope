#pragma once

#include "Rendering\WindowManager.h"
#include "Rendering\Renderer.h"

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
		Renderer m_Renderer;
	};

}

