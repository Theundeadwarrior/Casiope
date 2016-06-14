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

	int InitOpenGL()
	{
		/* Enable smooth shading */
		glShadeModel(GL_SMOOTH);

		/* Set the background black */
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		/* Depth buffer setup */
		glClearDepth(1.0f);

		/* Enables Depth Testing */
		glEnable(GL_DEPTH_TEST);

		/* The Type Of Depth Test To Do */
		glDepthFunc(GL_LEQUAL);

		/* Really Nice Perspective Calculations */
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		return 1;
	}

	/* function to reset our viewport after a window resize */
	int Display_SetViewport(int width, int height)
	{
		/* Height / width ration */
		GLfloat ratio;

		/* Protect against a divide by zero */
		if (height == 0) {
			height = 1;
		}

		ratio = (GLfloat)width / (GLfloat)height;

		/* Setup our viewport. */
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);

		/* change to the projection matrix and set our viewing volume. */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		///* Set our perspective */
		//gluPerspective(45.0f, ratio, 0.1f, 100.0f);

		/* Make sure we're chaning the model view and not the projection */
		glMatrixMode(GL_MODELVIEW);

		/* Reset The View */
		glLoadIdentity();

		return 1;
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

		m_Window = SDL_CreateWindow("Casiope", 100, 100, 1280, 720, SDL_WINDOW_SHOWN);
		if (m_Window == nullptr)
		{
			std::cout << "Error when creating SDL Window: " << SDL_GetError() << std::endl;
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
