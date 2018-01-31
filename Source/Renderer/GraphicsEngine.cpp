#include "GraphicsEngine.h"

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

#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 720
#define GRID_SIZE 16

namespace Renderer
{
	ShaderProgramId g_LightCullingProgram;
	GraphicsCore::ShaderStorageBufferResource g_SSBO;

	ShaderProgramId g_DepthPrePassProgram;
	GraphicsCore::FrameBufferResource g_FBO;

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

	int GraphicsEngine::InitializeLightGridCompute()
	{
		int workGroupsX = (SCREEN_SIZE_X + (SCREEN_SIZE_X % GRID_SIZE)) / GRID_SIZE;
		int workGroupsY = (SCREEN_SIZE_Y + (SCREEN_SIZE_Y % GRID_SIZE)) / GRID_SIZE;
		size_t numberOfTiles = workGroupsX * workGroupsY;

		g_LightCullingProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateComputeShaderProgram("shaders/frustum_grid.comp.glsl");
		g_SSBO.Init(16 * sizeof(float) * numberOfTiles, GraphicsCore::BufferUsage::StaticCopy, nullptr); // Frustrum are 4 planes of 4 floats
		
		g_DepthPrePassProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateVertexFragmentShaderProgram("shaders/depth.vert.glsl", "shaders/depth.frag.glsl");
		g_FBO.Init(SCREEN_SIZE_X, SCREEN_SIZE_Y);

		return 0;
	}

	int GraphicsEngine::Initialize()
	{
		// First, logger
		m_Logger = log4cxx::Logger::getLogger("GraphicsEngine");

		GraphicsResourceManager::CreateInstance();

		int result = m_WindowManager.InitWindow(SCREEN_SIZE_X, SCREEN_SIZE_Y);
		if (result != -1)
			result = InitializeGlew();
		if (result != -1)
			result = InitializeOpenGL();
		if (result != -1)
			result = InitializeLightGridCompute();

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

			GraphicsCore::GPUAPI::UseShader(shaderProgramId);
			BindViewProjMatrices(shaderProgramId, world);
			DrawModel(model);
		}
	}

	void GraphicsEngine::BindViewProjMatrices(ShaderProgramId shaderProgramId, Engine::World * world)
	{
		GLint viewLoc = glGetUniformLocation(shaderProgramId, "view");
		glm::mat4 viewMatrix = world->GetCamera()->GetViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		GLint projLoc = glGetUniformLocation(shaderProgramId, "projection");
		glm::mat4 projMatrix;
		((Engine::PerspectiveCamera*)(world->GetCamera()))->GetPerspectiveMat(projMatrix);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
	}

	void GraphicsEngine::DrawModel(const Model * model)
	{
		// Bind the model matrix
		GLint modelLoc = glGetUniformLocation(model->m_Material->m_ShaderProgram, "model");
		glm::mat4 modelMatrix;
		modelMatrix = glm::translate(modelMatrix, model->m_Transform.GetPosition());
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		// Bind the Shader Params
		model->m_Material->BindShaderParameters();
		GraphicsCore::GPUAPI::DrawCall(model->m_Mesh);
		model->m_Material->UnBindShaderParameters();
	}

	void GraphicsEngine::DepthPrePass(Engine::World* world) 
	{
		GraphicsCore::GPUAPI::UseShader(g_DepthPrePassProgram);

		BindViewProjMatrices(g_DepthPrePassProgram, world);

		glBindFramebuffer(GL_FRAMEBUFFER, g_FBO.FBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		auto models = world->GetModels();
		for (auto* model : *models)
		{
			GLint modelLoc = glGetUniformLocation(g_DepthPrePassProgram, "model");
			glm::mat4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, model->m_Transform.GetPosition());
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			GraphicsCore::GPUAPI::DrawCall(model->m_Mesh);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
					// New renderer:
					// Step 1: Depth pre-pass.
					DepthPrePass(world);

					// Step 2: Render the scene.
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
		m_WindowManager.SwapCurrentWindow();
	}
}
