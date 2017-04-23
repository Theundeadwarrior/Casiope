#include "GraphicsEngine.h"
#include <iostream>
#include <SDL.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/World/WorldManager.h"
#include "Engine/Camera/PerspectiveCamera.h"

#include "GraphicsCore/LowLevelAPI/LowLevelGPUAPI.h"
#include "GraphicsCore/RenderState/RenderState.h"
#include "GraphicsCore/Shaders/Shader.h"
#include "GraphicsCore/Geometry/Geometry.h"
#include "GraphicsCore/LowLevelAPI/LowLevelGPUResource.h"

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
		glewExperimental = GL_TRUE;
		
		LOG4CXX_INFO(m_Logger, "GLEW initializing");
		GLenum glewInitialization = glewInit();

		if (glewInitialization != GLEW_OK)
		{
			// On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
			LOG4CXX_ERROR(m_Logger, "Could no initialize GLEW: " << glewGetErrorString(glewInitialization));

			// On quitte la SDL
			m_WindowManager.ShutdownWindow();

			return -1;
		}

		LOG4CXX_INFO(m_Logger, "GLEW initialized");
		return 0;
	}

	int GraphicsEngine::InitializeOpenGL()
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		LOG4CXX_INFO(m_Logger, "Renderer: " << renderer);
		LOG4CXX_INFO(m_Logger, "OpenGL version supported: " << version);

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

		return 0;
	}

	int GraphicsEngine::Initialize()
	{
		// First, logger
		m_Logger = log4cxx::Logger::getLogger("GraphicsEngine");

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
	GraphicsCore::Geometry g_Geometry;
	GLuint VAO = 0;// , vao2 = 0;

	void GraphicsEngine::InitTestGraphics()
	{
		GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		g_Geometry.m_GPUParams.m_VAO = GraphicsCore::BuildVertexBufferFromVertexArray(GraphicsCore::GeometryGPUType::V3FT2F, vertices, sizeof(vertices));

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
	}

	glm::vec3 cubePositions[] = {
		glm::vec3(5.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 5.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.0f)
	};

	void DrawOpaqueObjects(Engine::World* world)
	{
		GLint modelLoc = glGetUniformLocation(g_ShaderProgram->GetProgramId(), "model");
		GLint viewLoc = glGetUniformLocation(g_ShaderProgram->GetProgramId(), "view");
		GLint projLoc = glGetUniformLocation(g_ShaderProgram->GetProgramId(), "projection");

		glm::mat4 viewMatrix = world->GetCamera()->GetViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		glm::mat4 projMatrix;
		((Engine::PerspectiveCamera*)(world->GetCamera()))->GetPerspectiveMat(projMatrix);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));


		for (GLuint i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			GraphicsCore::GPUAPI::DrawCall(&g_Geometry, g_ShaderProgram);
		}
	}

	void GraphicsEngine::RenderWorld(Engine::World* world)
	{
		////todo : add visibility system outside and iterate on visible objects only

		//// Skybox
		//DrawSkyBox(world);

		GraphicsCore::RenderState::EnableDepthRead();
		//{
		//	//Opaque objects
			GraphicsCore::RenderState::EnableDepthWrite();
		//	{
				GraphicsCore::RenderState::EnableBackFaceCulling();
		//		{
					DrawOpaqueObjects(world);
		//		}
				GraphicsCore::RenderState::DisableBackFaceCulling();
		//		//-----------------------------------------------------------------------------
		//		//Opaque objects with holes (if we know the information?)
		//		//draw
		//	}
		//	DrawDebugInfo(scene); // for debug only
			GraphicsCore::RenderState::DisableDepthWrite();


		//	//-----------------------------------------------------------------------------
		//	//Alpha
			//GraphicsCore::RenderState::EnableAlphaBlending();
		//	{
		//		//-----------------------------------------------------------------------------
		//		// draw alpha objects
		//		//-----------------------------------------------------------------------------
		//		LowLevelGraphics::LowLevelAPI::SetAlphaBlendFunc();

		//		DrawAlphaObjects(scene);

		//	}
			//GraphicsCore::RenderState::DisableAlphaBlending();
			//}
		GraphicsCore::RenderState::DisableDepthRead();
	}

	void GraphicsEngine::StartRendering()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		GraphicsCore::RenderState::EnableDepthWrite();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GraphicsCore::RenderState::DisableDepthWrite();

	}

	void GraphicsEngine::EndRendering()
	{
		SDL_GL_SwapWindow(m_WindowManager.GetCurrentWindow());
	}
}
