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
#include "GraphicsCore/Mesh/Mesh.h"
#include "GraphicsCore/LowLevelAPI/LowLevelGPUResource.h"

#include "Renderer/Resource/GraphicsResourceManager.h"
#include "Renderer/Model/Model.h"
#include "Renderer/Material/Material.h"

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

	int GraphicsEngine::Shutdown()
	{
		int result = 0;
		result = m_WindowManager.ShutdownWindow();

		GraphicsResourceManager::DestroyInstance();

		return result;
	}

	void GraphicsEngine::DrawOpaqueObjects(Engine::World* world)
	{
		auto models = world->GetModels();
		for (auto* model : *models)
		{
			auto shaderProgramId = model->m_Material->m_ShaderProgram;

			GLint modelLoc = glGetUniformLocation(shaderProgramId, "model");
			GLint viewLoc = glGetUniformLocation(shaderProgramId, "view");
			GLint projLoc = glGetUniformLocation(shaderProgramId, "projection");

			glm::mat4 viewMatrix = world->GetCamera()->GetViewMatrix();
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

			glm::mat4 projMatrix;
			((Engine::PerspectiveCamera*)(world->GetCamera()))->GetPerspectiveMat(projMatrix);
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

			glm::mat4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, model->m_Transform.GetPosition());
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			DrawModel(model);
		}


	}

	void GraphicsEngine::DrawModel(const Model * model)
	{
		glActiveTexture(GL_TEXTURE0);
		// todo: Move that to the bind 
		TextureMaterial* texMat = dynamic_cast<TextureMaterial*>(model->m_Material);
		glBindTexture(GL_TEXTURE_2D, texMat->m_Texture);
		GraphicsCore::GPUAPI::DrawCall(model->m_Mesh, model->m_Material->m_ShaderProgram);
		glBindTexture(GL_TEXTURE_2D, 0);
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
