#pragma once

#include <SDL.h>

#include "Core/Input/InputManager.h"
#include "Core/Singleton/Singleton.h"
#include "Engine/World/WorldManager.h"
#include "Renderer/GraphicsEngine.h"

namespace Engine
{
	class GameEngine : public Core::Singleton<GameEngine>
	{
	public:
		SINGLETON_DECLARATION(GameEngine);

		void Initialize();
		void Shutdown();

		void HandleEvents();

		int Loop();

		WorldManager& GetWorldManager() { return m_WorldManager; }
		Renderer::GraphicsEngine& GetGraphicsEngine() { return m_Renderer; }

		// Getters
		Core::InputManager& GetInputManager() { return m_InputManager; }

	private:
		GameEngine();
		~GameEngine();

		Renderer::GraphicsEngine m_Renderer;
		Core::InputManager m_InputManager;
		WorldManager m_WorldManager;

		SDL_Event m_CurrentEvent;

		bool m_RequestedQuit;
	};
}
