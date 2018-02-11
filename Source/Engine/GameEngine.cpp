
#include "GameEngine.h"

#include "Core/File/FileSystem.h"

#include <iostream>
#include <time.h>
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

		srand(0);
	}

	void GameEngine::Shutdown()
	{
		// todo remove
		World* world = m_WorldManager.GetCurrentWorld();
		m_WorldManager.SetCurrentWorld(nullptr);
		delete world;
		// endtodo

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

	int GameEngine::Loop()
	{
		// Loop
		while (!m_RequestedQuit)
		{
			HandleEvents();
			m_InputManager.Update();
			m_WorldManager.Update();

			m_Renderer.StartRendering();
			m_Renderer.RenderWorld(m_WorldManager.GetCurrentWorld()); // TODO lcharbonneau: We shouldn't the entire world!
			m_Renderer.EndRendering();
		}
		return 0;
	}


}
