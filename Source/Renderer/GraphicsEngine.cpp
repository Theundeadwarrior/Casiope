#include "GraphicsEngine.h"
#include <iostream>
#include <SDL.h>


#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	int InitializeOpenGL()
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		printf("Renderer: %s\n", renderer);
		printf("OpenGL version supported %s\n", version);

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

		return 0;
	}

	int GraphicsEngine::Initialize()
	{
		int result = m_WindowManager.InitWindow();
		if (result != -1)
			result = InitializeGlew();
		if (result != -1)
			result = InitializeOpenGL();


		return result;
	}

	int GraphicsEngine::Shutdown()
	{
		return m_WindowManager.ShutdownWindow();
	}

	// REMOVE THIS
	GraphicsCore::ShaderProgram* g_ShaderProgram;
	GLuint vao1 = 0, vao2 = 0;

	void GraphicsEngine::InitTestGraphics()
	{
		GLfloat vertices[] = {
			// First triangle
			-0.9f, -0.5f, 0.0f,  // Left 
			-0.0f, -0.5f, 0.0f,  // Right
			-0.45f, 0.5f, 0.0f,  // Top 
								 // Second triangle
								 0.0f, -0.5f, 0.0f,  // Left
								 0.9f, -0.5f, 0.0f,  // Right
								 0.45f, 0.5f, 0.0f   // Top
		};

		GLuint vbo1 = 0, vbo2 = 0, ebo = 0;

		glGenVertexArrays(1, &vao1);
		glGenVertexArrays(1, &vao2);
		glGenBuffers(1, &vbo1);
		glGenBuffers(1, &ebo);
		glGenBuffers(1, &vbo2);


		glBindVertexArray(vao1);
			glBindBuffer(GL_ARRAY_BUFFER, vbo1);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
			glEnableVertexAttribArray(0);
		glBindVertexArray(vao2);
			glBindBuffer(GL_ARRAY_BUFFER, vbo2);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + 9, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
			glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		const char* vertex_shader =
			"#version 400\n"
			"in vec3 vp;"
			"uniform mat4 model;"
			"uniform mat4 view;"
			"uniform mat4 projection;"
			"void main () {"
			"  gl_Position = projection * view * model *  vec4 (vp, 1.0);"
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

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
		model = glm::rotate(model, 45.f, glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		unsigned int windowSize[2];
		m_WindowManager.GetCurrentWindowSize(windowSize[0], windowSize[1]);

		proj = glm::perspective(45.0f, (GLfloat)windowSize[0] / (GLfloat)windowSize[1], 0.1f, 100.0f);

		GLint modelLoc = glGetUniformLocation(g_ShaderProgram->GetProgramId(), "model");
		GLint viewLoc = glGetUniformLocation(g_ShaderProgram->GetProgramId(), "view");
		GLint projLoc = glGetUniformLocation(g_ShaderProgram->GetProgramId(), "projection");

		// Pass them to the shaders
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUseProgram(g_ShaderProgram->GetProgramId());
		glBindVertexArray(vao1);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vao2);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(m_WindowManager.GetCurrentWindow());
	}

}
