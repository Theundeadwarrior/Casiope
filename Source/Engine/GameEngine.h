#pragma once

#include "Core\Input\InputManager.h"
#include "Engine\World\WorldManager.h"
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
		Renderer::GraphicsEngine m_Renderer;
		Core::InputManager m_InputManager;
		WorldManager m_WorldManager;

	};

}

