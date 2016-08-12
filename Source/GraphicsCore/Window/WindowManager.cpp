#include "GraphicsCore/Window/WindowManager.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
namespace GraphicsCore
{
	WindowManager::WindowManager()
	{
	}


	WindowManager::~WindowManager()
	{
	}

	int WindowManager::InitWindow()
	{
		// Initialisation de la SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Error when initializing SDL : " << SDL_GetError() << std::endl;
			SDL_Quit();
			return -1;
		}

		// Version d'OpenGL
#ifdef _LINUX_
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#else
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
#endif

		// Double Buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		m_Window = SDL_CreateWindow("Casiope", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (m_Window == nullptr)
		{
			std::cout << "Error when creating SDL Window: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return -1;
		}

		m_GLContext = SDL_GL_CreateContext(m_Window);

		if (m_GLContext == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_Window);
			SDL_Quit();

			return -1;
		}

		SDL_ShowCursor(0);

		return 0;
	}

	void WindowManager::GetCurrentWindowSize(unsigned int& o_x, unsigned int& o_y) const
	{
		GLint m_viewport[4];
		glGetIntegerv(GL_VIEWPORT, m_viewport);
		o_x = m_viewport[2];
		o_y = m_viewport[3];
	}

	int WindowManager::ShutdownWindow()
	{
		// On quitte la SDL
		SDL_GL_DeleteContext(m_GLContext);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
		return 0;
	}
}

