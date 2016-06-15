#include "Rendering\Renderer.h"
#include <iostream>
#include <SDL.h>


#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

namespace Engine
{
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
	}

	int Renderer::InitializeGlew()
	{

#ifdef _WIN32
		GLenum glewInitialization(glewInit());

		if (glewInitialization != GLEW_OK)
		{
			// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

			std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(glewInitialization) << std::endl;


			// On quitte la SDL
			m_WindowManager.ShutdownWindow();
				
			return -1;
		}
#endif
	}

	int Renderer::Initialize()
	{
		int result = m_WindowManager.InitWindow();
		if (result != -1)
			InitializeGlew();

		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

		return result;
	}

	int Renderer::Shutdown()
	{
		return m_WindowManager.ShutdownWindow();
	}


	void Renderer::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableVertexAttribArray(0);
		float vertices[] = { -0.5, -0.5, 0,   0.0, 0.5,  0, 0.5, -0.5 ,0};
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);


		SDL_GL_SwapWindow(m_WindowManager.GetCurrentWindow());
	}

}
