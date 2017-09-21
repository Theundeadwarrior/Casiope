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

#include "Renderer/Resource/GraphicsResourceManager.h"
#include "Renderer/Mesh/Mesh.h"

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

		GraphicsResourceManager::CreateInstance();

		int result = m_WindowManager.InitWindow();
		if (result != -1)
			result = InitializeGlew();
		if (result != -1)
			result = InitializeOpenGL();


		return result;
	}


	GraphicsCore::Geometry g_Geometry;
	ShaderProgramId g_ShaderProgramId;


	int GraphicsEngine::Shutdown()
	{
		int result = 0;
		result = m_WindowManager.ShutdownWindow();

		GraphicsResourceManager::DestroyInstance();

		return result;
	}



	void GraphicsEngine::InitTestGraphics()
	{
		GLfloat vertices[] = {
			// Back face
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left    

			// Front face
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        

			// Left face
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right

			// Right face
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left

			// Bottom face          
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right

			// Top face
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left    
		};

		g_Geometry.UpdateGeometry(vertices, sizeof(vertices), GraphicsCore::GeometryGPUType::V3FT2F);

		g_ShaderProgramId = GraphicsResourceManager::GetInstance()->GetShaderManager().LinkShadersIntoProgram("shaders/basic_shader.vx", "shaders/basic_shader.fg");
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

	void GraphicsEngine::DrawOpaqueObjects(Engine::World* world)
	{
		GLint modelLoc = glGetUniformLocation(g_ShaderProgramId, "model");
		GLint viewLoc = glGetUniformLocation(g_ShaderProgramId, "view");
		GLint projLoc = glGetUniformLocation(g_ShaderProgramId, "projection");

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

			GraphicsCore::GPUAPI::DrawCall(&g_Geometry, g_ShaderProgramId);
		}

		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesh* mesh = world->GetMesh();
		GraphicsCore::Geometry* worldGeometry = GraphicsResourceManager::GetInstance()->GetGeometryManager().GetGeometry(mesh->m_GeometryId);
		GraphicsCore::GPUAPI::DrawCall(worldGeometry, g_ShaderProgramId);
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
				GraphicsCore::RenderState::EnableBackFaceCulling(); // todo lcharbonneau: move that to the mesh property.
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
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		GraphicsCore::RenderState::EnableDepthWrite();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GraphicsCore::RenderState::DisableDepthWrite();

	}

	void GraphicsEngine::EndRendering()
	{
		SDL_GL_SwapWindow(m_WindowManager.GetCurrentWindow());
	}
}
