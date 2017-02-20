#include "GameEngine.h"
#include <iostream>
#include <SDL.h>


#include "Camera/PerspectiveCamera.h"
#include "GraphicsCore/Textures/Texture.h"
#include "Renderer/SkyBox/SkyBox.h"
#include "Core/File/ImageUtilities.h"

#include "Engine/Resource/ResourceManager.h"


namespace Engine
{
	GameEngine::GameEngine()
	{
	}

	GameEngine::~GameEngine()
	{
	}

	void GameEngine::Initialize()
	{
		m_Renderer.Initialize();
		ResourceManager::CreateInstance();

		m_InputManager.SetResetMouseBehavior(true); // todo: this needs to be handled in the StateManager
		m_InputManager.SetResetMouseValues(400, 200); // todo: this needs to be handled in the StateManager
		m_InputManager.ResetMouseToCenter();
	}

	void GameEngine::Shutdown()
	{
		// todo remove
		World* world = m_WorldManager.GetCurrentWorld();
		m_WorldManager.SetCurrentWorld(nullptr);
		delete world;
		// endtodo

		ResourceManager::DestroyInstance();
		m_Renderer.Shutdown();
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
				exit(0);
				return;
			}
		}
	}

	int GameEngine::Loop()
	{
		// Loop
		while (true)
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
