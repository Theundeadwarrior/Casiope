#pragma once

#include "Core/Input/InputManager.h"
#include "Core/Singleton/Singleton.h"
#include "Engine/World/WorldManager.h"
#include "Engine/State/State.h"
#include "Renderer/GraphicsEngine.h"

#include <SDL.h>
#include <vector>

namespace Engine
{
	class GameEngine : public Core::Singleton<GameEngine>
	{
	public:
		SINGLETON_DECLARATION(GameEngine);

		void Initialize();

		void PushState(IState* state);
		void PopState();
		void Shutdown();

		void Loop();

		Core::InputManager& GetInputManager() { return m_InputManager; }
		Renderer::GraphicsEngine& GetRenderer() { return m_Renderer; }

	private:
		GameEngine();
		~GameEngine();

		void HandleEvents();

	private:
		std::vector<IState*> m_States;

		Renderer::GraphicsEngine m_Renderer;
		Core::InputManager m_InputManager;

		SDL_Event m_CurrentEvent;

		bool m_RequestedQuit; // todo : move to a state.
	};
}
