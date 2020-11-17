#include "GraphicsEngine.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/World/World.h"
#include "Engine/Camera/PerspectiveCamera.h"

#include "GraphicsCore/LowLevelAPI/LowLevelGPUAPI.h"
#include "GraphicsCore/RenderState/RenderState.h"
#include "GraphicsCore/Shaders/Shader.h"
#include "GraphicsCore/Mesh/Mesh.h"
#include "GraphicsCore/LowLevelAPI/LowLevelGPUResource.h"

#include "Renderer/Resource/GraphicsResourceManager.h"
#include "Renderer/Model/Model.h"
#include "Renderer/Light/Light.h"
#include "Renderer/Material/Material.h"
#include "Renderer/SkyBox/SkyBox.h"

#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 720
#define GRID_SIZE 16

namespace Renderer
{
	bool g_IsGridComputeSetup = false;
	ShaderProgramId g_GridComputeProgram;
	GraphicsCore::ShaderStorageBufferResource g_FrustrumSSBO;
	GraphicsCore::ShaderStorageBufferResource g_LightBufferSSBO;
	GraphicsCore::ShaderStorageBufferResource g_OpaqueLightGridSSBO;
	GraphicsCore::ShaderStorageBufferResource g_TransparentLightGridSSBO;
	GraphicsCore::ShaderStorageBufferResource g_OpaqueLightIndexListSSBO;
	GraphicsCore::ShaderStorageBufferResource g_TransparentLightIndexListSSBO;
	GraphicsCore::ShaderStorageBufferResource g_OpaqueLightIndexCounterSSBO;
	GraphicsCore::ShaderStorageBufferResource g_TransparentLightIndexCounterSSBO;

	// DEBUGGING
	struct Float4Data {
		Float4Data(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		float x, y, z, w;
	};
	Float4Data* debugLightVertexBuffer = nullptr;

	GraphicsCore::Mesh lightMesh;
	ShaderProgramId g_LightDebugProgram;
	// END OF DEBUGGING

	ShaderProgramId g_DepthPrePassProgram;
	GraphicsCore::FrameBufferResource g_DepthPrePassFBO;

	ShaderProgramId g_LightCullingProgram;

	GraphicsEngine::GraphicsEngine()
	{
	}

	GraphicsEngine::~GraphicsEngine()
	{
	}

	int GraphicsEngine::InitializeGlew()
	{
		glewExperimental = GL_TRUE;

		GRAPHICS_LOG()->info("GLEW initializing");
		GLenum glewInitialization = glewInit();

		if (glewInitialization != GLEW_OK)
		{
			GRAPHICS_LOG()->error("Could no initialize GLEW: {}", glewGetErrorString(glewInitialization));

			// On quitte la SDL
			m_WindowManager.ShutdownWindow();

			return -1;
		}

		GRAPHICS_LOG()->info("GLEW initialized");
		return 0;
	}

	int GraphicsEngine::InitializeOpenGL()
	{
		const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
		const GLubyte* version = glGetString(GL_VERSION); // version as a string
		GRAPHICS_LOG()->info("Renderer: {}", renderer);
		GRAPHICS_LOG()->info("OpenGL version supported: {}", version);

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

		g_GridComputeProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateComputeShaderProgram("shaders/frustum_grid.comp.glsl");
		g_DepthPrePassProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateVertexFragmentShaderProgram("shaders/depth.vert.glsl", "shaders/depth.frag.glsl");
		g_LightCullingProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateComputeShaderProgram("shaders/light_culling.comp.glsl");

		g_DepthPrePassFBO.Init(SCREEN_SIZE_X, SCREEN_SIZE_Y);
		g_LightBufferSSBO.Init(1024 * sizeof(Renderer::Light), GraphicsCore::BufferUsage::DynamicDraw, nullptr);
		g_FrustrumSSBO.Init(16 * sizeof(float) * numberOfTiles, GraphicsCore::BufferUsage::StaticCopy, nullptr);
		g_OpaqueLightGridSSBO.Init(numberOfTiles * 2 * sizeof(uint32_t), GraphicsCore::BufferUsage::StaticCopy, nullptr);
		g_TransparentLightGridSSBO.Init(numberOfTiles * 2 * sizeof(uint32_t), GraphicsCore::BufferUsage::DynamicCopy, nullptr);
		g_OpaqueLightIndexListSSBO.Init(512 * 1024 * sizeof(uint32_t), GraphicsCore::BufferUsage::DynamicCopy, nullptr);
		g_TransparentLightIndexListSSBO.Init(512 * 1024 * sizeof(uint32_t), GraphicsCore::BufferUsage::DynamicCopy, nullptr);
		g_OpaqueLightIndexCounterSSBO.Init(1 * sizeof(uint32_t), GraphicsCore::BufferUsage::DynamicCopy, nullptr);
		g_TransparentLightIndexCounterSSBO.Init(1 * sizeof(uint32_t), GraphicsCore::BufferUsage::DynamicCopy, nullptr);

		// DEBUGGING!!! TO REMOVE!!!
		g_LightDebugProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateVertexFragmentShaderProgram("shaders/light_debug.vert.glsl", "shaders/light_debug.frag.glsl");

		return 0;
	}

	int GraphicsEngine::Initialize()
	{
		GraphicsResourceManager::CreateInstance();

		int result = m_WindowManager.CreateNewWindow(SCREEN_SIZE_X, SCREEN_SIZE_Y);
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

	void GraphicsEngine::GridComputePass(const glm::mat4& projMatrix)
	{
		int workGroupsX = (SCREEN_SIZE_X + (SCREEN_SIZE_X % GRID_SIZE)) / GRID_SIZE;
		int workGroupsY = (SCREEN_SIZE_Y + (SCREEN_SIZE_Y % GRID_SIZE)) / GRID_SIZE;

		GraphicsCore::GPUAPI::UseShader(g_GridComputeProgram);

		// Setup inverse projection Matrix.
		glm::mat4 projInv = glm::inverse(projMatrix);
		glUniformMatrix4fv(glGetUniformLocation(g_GridComputeProgram, "inverseProj"), 1, GL_FALSE, glm::value_ptr(projInv));

		glUniform2f(glGetUniformLocation(g_GridComputeProgram, "screenDimensions"), SCREEN_SIZE_X, SCREEN_SIZE_Y);

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, g_FrustrumSSBO.SSBO);
		glDispatchCompute(workGroupsX, workGroupsY, 1);
	}

	void GraphicsEngine::LightCullingPass(Engine::World * world)
	{
		int workGroupsX = (SCREEN_SIZE_X + (SCREEN_SIZE_X % GRID_SIZE)) / GRID_SIZE;
		int workGroupsY = (SCREEN_SIZE_Y + (SCREEN_SIZE_Y % GRID_SIZE)) / GRID_SIZE;

		GraphicsCore::GPUAPI::UseShader(g_LightCullingProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_DepthPrePassFBO.texId);

		glm::mat4 projInv = glm::inverse(*(world->GetCamera()->GetPerspectiveMat()));
		glUniformMatrix4fv(glGetUniformLocation(g_LightCullingProgram, "inverseProj"), 1, GL_FALSE, glm::value_ptr(projInv));

		auto* lights = world->GetLights();
		glUniform1ui(glGetUniformLocation(g_LightCullingProgram, "numLights"), static_cast<uint32_t>(lights->size()));
	
		// DEBUGGING STUFF TO REMOVE!!!!
		for (int i = 0; i < lights->size(); i++) {
			Light& light = (*lights)[i];
			float min = 0;
			float max = 16;
			glm::vec4 pos = light.GetWorldSpacePosition();

			//int test = rand() % 3;

			light.SetWorldSpacePosition(glm::vec4(fmod((pos.x + (-4.5f * 0.01f) - min + max), max) + min, pos.y, pos.z, 1.0f));
		}
		// END OF DEBUGGING STUFF!!!

		for(uint32_t i = 0; i < world->GetLights()->size(); ++i)
		{
			(*lights)[i].UpdateViewSpaceCoord(world->GetCamera()->GetViewMatrix());
		}

		g_LightBufferSSBO.Init(world->GetLights()->size() * sizeof(Renderer::Light), GraphicsCore::BufferUsage::DynamicDraw, static_cast<void*>(world->GetLights()->data()));

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, g_LightBufferSSBO.SSBO);

		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, g_FrustrumSSBO.SSBO);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, g_OpaqueLightGridSSBO.SSBO);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, g_TransparentLightGridSSBO.SSBO);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, g_OpaqueLightIndexListSSBO.SSBO);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, g_TransparentLightIndexListSSBO.SSBO);

		uint32_t opaqueLightInitValue = 0;
		g_OpaqueLightIndexCounterSSBO.Init(1 * sizeof(uint32_t), GraphicsCore::BufferUsage::DynamicCopy, &opaqueLightInitValue);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, g_OpaqueLightIndexCounterSSBO.SSBO);

		uint32_t transparentLightInitValue = 0;
		g_TransparentLightIndexCounterSSBO.Init(1 * sizeof(uint32_t), GraphicsCore::BufferUsage::DynamicCopy, &opaqueLightInitValue);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, g_TransparentLightIndexCounterSSBO.SSBO);

		glDispatchCompute(workGroupsX, workGroupsY, 1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GraphicsEngine::DrawOpaqueObjects(Engine::World* world)
	{
		auto models = world->GetModels();
		for (auto* model : *models)
		{
			auto shaderProgramId = model->m_Material->m_ShaderProgram;

			GraphicsCore::GPUAPI::UseShader(shaderProgramId);
			BindViewProjMatrices(shaderProgramId, world);

			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, g_LightBufferSSBO.SSBO);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, g_OpaqueLightGridSSBO.SSBO);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, g_OpaqueLightIndexListSSBO.SSBO);

			int workGroupsX = (SCREEN_SIZE_X + (SCREEN_SIZE_X % GRID_SIZE)) / GRID_SIZE;
			glUniform1i(glGetUniformLocation(shaderProgramId, "workGroupsX"), workGroupsX);

			DrawModel(model);
		}

		// DEBUGGING LIGHTS
		//DrawDebugLights(world);
	}

	void GraphicsEngine::DrawDebugLights(Engine::World * world)
	{
		if (debugLightVertexBuffer == nullptr)
		{
			debugLightVertexBuffer = static_cast<Float4Data*>(malloc(world->GetLights()->size() * 6 * 6 * sizeof(Float4Data)));
		}
		{
			std::vector<Renderer::Light>* lights = world->GetLights();
			uint32_t currentVertex = 0;
			for (int i = 0; i < world->GetLights()->size(); ++i)
			{
				Renderer::Light& light = (*lights)[i];
				glm::vec4 pos = light.GetWorldSpacePosition();

				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);

				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);

				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);

				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);

				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y - 0.05f, pos.z + 0.05f, 1);

				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x + 0.05f, pos.y + 0.05f, pos.z + 0.05f, 1);
				debugLightVertexBuffer[currentVertex++] = Float4Data(pos.x - 0.05f, pos.y + 0.05f, pos.z - 0.05f, 1);
			}
			lightMesh.UpdateGeometry(static_cast<void*>(debugLightVertexBuffer), currentVertex * 4 * sizeof(float), GraphicsCore::VertexBufferType::V4F);
		}
		GraphicsCore::GPUAPI::UseShader(g_LightDebugProgram);
		BindViewProjMatrices(g_LightDebugProgram, world);
		GraphicsCore::GPUAPI::DrawCall(&lightMesh);
		// END OF DEBUGGING LIGHTS
	}

	void GraphicsEngine::BindViewProjMatrices(ShaderProgramId shaderProgramId, Engine::World * world)
	{
		GLint viewLoc = glGetUniformLocation(shaderProgramId, "view");
		glm::mat4 viewMatrix = world->GetCamera()->GetViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		GLint projLoc = glGetUniformLocation(shaderProgramId, "projection");
		glm::mat4 projMatrix;
		world->GetCamera()->GetPerspectiveMat(projMatrix);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
	}

	void GraphicsEngine::DrawSkyBox(Engine::World* world)
	{
		Model* skybox = world->GetSkyBox();
		if (skybox != nullptr)
		{
			GraphicsCore::GPUAPI::UseShader(skybox->m_Material->m_ShaderProgram);

			GLint viewLoc = glGetUniformLocation(skybox->m_Material->m_ShaderProgram, "view");
			glm::mat4 viewMatrix = glm::mat4(glm::mat3(world->GetCamera()->GetViewMatrix()));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

			GLint projLoc = glGetUniformLocation(skybox->m_Material->m_ShaderProgram, "projection");
			glm::mat4 projMatrix;
			world->GetCamera()->GetPerspectiveMat(projMatrix);
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));


			GLint modelLoc = glGetUniformLocation(skybox->m_Material->m_ShaderProgram, "model");
			glm::mat4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, skybox->m_Transform.GetPosition());
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			skybox->m_Material->BindShaderParameters();
			GraphicsCore::GPUAPI::DrawCall(skybox->m_Mesh);
			skybox->m_Material->UnBindShaderParameters();
		}
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

		glBindFramebuffer(GL_FRAMEBUFFER, g_DepthPrePassFBO.FBO);
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
		//if (!g_IsGridComputeSetup)
		{
			glm::mat4 projMatrix;
			world->GetCamera()->GetPerspectiveMat(projMatrix);
			GridComputePass(projMatrix);

			g_IsGridComputeSetup = true;
		}

		////todo : add visibility system outside and iterate on visible objects only
		//// Skybox
		DrawSkyBox(world);

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

					// Step 2: Light Culling.
					LightCullingPass(world);

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
