#include "GameEngine.h"
#include <iostream>
#include "GameEngine.h"

#include <SDL.h>

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
	}

	void GameEngine::Shutdown()
	{
		m_Renderer.Shutdown();
	}

	int GameEngine::Loop()
	{
		// Loop
		SDL_Event events;
		while (true)
		{
			SDL_WaitEvent(&events);
			if (events.window.event == SDL_WINDOWEVENT_CLOSE)
				break;

			m_Renderer.Render();
		}
		return 0;
	}


}
