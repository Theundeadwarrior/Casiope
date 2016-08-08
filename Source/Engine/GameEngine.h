#pragma once

#include "Core/Input/InputManager.h"
#include "Engine/World/WorldManager.h"
#include "Renderer/GraphicsEngine.h"



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

		WorldManager& GetWorldManager() { return m_WorldManager; }
		Renderer::GraphicsEngine& GetGraphicsEngine() { return m_Renderer; }

	private:
		Renderer::GraphicsEngine m_Renderer;
		Core::InputManager m_InputManager;
		WorldManager m_WorldManager;

	};

}

