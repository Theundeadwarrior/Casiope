
#include "GameEngine.h"

#include "Core/File/FileSystem.h"

#include <iostream>
#include <SDL.h>

namespace Engine
{
	GameEngine::GameEngine()
		: m_RequestedQuit(false)
	{
	}

	GameEngine::~GameEngine()
	{
	}

	void GameEngine::Initialize()
	{
		Core::FileSystem::CreateInstance();
		m_Renderer.Initialize();

		m_InputManager.SetResetMouseBehavior(true); // todo: this needs to be handled in the StateManager
		m_InputManager.SetResetMouseValues(400, 200); // todo: this needs to be handled in the StateManager
		m_InputManager.ResetMouseToCenter();

		m_WorkerThread.Init(&m_WorkQueue);
	}

	void GameEngine::PushState(IState* state)
	{
		m_States.push_back(state);
		state->OnEnter();
	}

	void GameEngine::PopState()
	{
		assert(m_States.size() >= 1);
		auto* state = m_States.back();
		state->OnExit();
		m_States.pop_back();
	}

	void GameEngine::Shutdown()
	{
		while (m_States.size() != 0)
		{
			PopState();
		}

		m_WorkerThread.Shutdown();

		m_Renderer.Shutdown();
		Core::FileSystem::DestroyInstance();
	}

	void GameEngine::HandleEvents()
	{
		while (SDL_PollEvent(&m_CurrentEvent))
		{
			if (m_CurrentEvent.type == SDL_KEYDOWN || m_CurrentEvent.type == SDL_KEYUP)
			{
				m_InputManager.HandleEvent(m_CurrentEvent);
				break;
			}
			else if (m_CurrentEvent.type == SDL_WINDOWEVENT)
			{
				switch (m_CurrentEvent.window.event)
				{
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					m_InputManager.SetResetMouseBehavior(true);
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					m_InputManager.SetResetMouseBehavior(false);
					break;
				}
			}
			else if (m_CurrentEvent.type == SDL_QUIT)
			{
				m_RequestedQuit = true;
			}
		}
	}

	void GameEngine::Loop()
	{
		// Loop
		while (!m_RequestedQuit)
		{
			HandleEvents();
			m_InputManager.Update();

			for (auto* state : m_States)
			{
				state->Update();
			}
		}
	}


}
