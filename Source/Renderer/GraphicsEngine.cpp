#include "GraphicsEngine.h"
#include <iostream>
#include <SDL.h>


#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include "GraphicsCore\Shaders\Shader.h"

namespace Renderer
{
	GraphicsEngine::GraphicsEngine()
	{
	}


	GraphicsEngine::~GraphicsEngine()
	{
	}

	int GraphicsEngine::InitializeGlew()
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

	int GraphicsEngine::Initialize()
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

	int GraphicsEngine::Shutdown()
	{
		return m_WindowManager.ShutdownWindow();
	}

	// REMOVE THIS
	GraphicsCore::ShaderProgram* g_ShaderProgram;
	GLuint vao = 0;

	void GraphicsEngine::InitTestGraphics()
	{
		GLfloat vertices[] = {
			0.5f,  0.5f, 0.0f,  // Top Right
			0.5f, -0.5f, 0.0f,  // Bottom Right
			-0.5f, -0.5f, 0.0f,  // Bottom Left
			-0.5f,  0.5f, 0.0f   // Top Left 
		};
		GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3,   // First Triangle
			1, 2, 3    // Second Triangle
		};

		GLuint vbo = 0, ebo = 0;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);


		glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
			glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		const char* vertex_shader =
			"#version 400\n"
			"in vec3 vp;"
			"void main () {"
			"  gl_Position = vec4 (vp, 1.0);"
			"}";

		const char* fragment_shader =
			"#version 400\n"
			"out vec4 frag_colour;"
			"void main () {"
			"  frag_colour = vec4 (1.0f, 0.5f, 0.2f, 1.0f);"
			"}";

		g_ShaderProgram = new GraphicsCore::ShaderProgram(vertex_shader, fragment_shader, "");
		// Need to move everything up somewhere else...
	}


	void GraphicsEngine::Render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(g_ShaderProgram->GetProgramId());
		glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(m_WindowManager.GetCurrentWindow());
	}

}
