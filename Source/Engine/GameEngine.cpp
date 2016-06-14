#include "GameEngine.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include "GameEngine.h"

namespace Core
{
	GameEngine::GameEngine()
	{
	}

	GameEngine::~GameEngine()
	{
	}

	int GameEngine::InitWindow()
	{
		// Initialisation de la SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Error when initializing SDL : " << SDL_GetError() << std::endl;
			SDL_Quit();
			return -1;
		}

		m_Window = SDL_CreateWindow("Casiope", 100, 100, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (m_Window == nullptr)
		{
			std::cout << "Error when creating SDL Window: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return -1;
		}


		// Version d'OpenGL
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Double Buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		m_GLContext = SDL_GL_CreateContext(m_Window);

		if (m_GLContext == 0)
		{
			std::cout << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_Window);
			SDL_Quit();

			return -1;
		}




		return 0;
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
		}
		return 0;
	}

	int GameEngine::ShutdownWindow()
	{
		// On quitte la SDL
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
		return 0;
	}

}
