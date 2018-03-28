#pragma once

#include "Core/Logging/Logger.h"
#include "GraphicsCore/GraphicsType.h"
#include "GraphicsCore/Window/WindowManager.h"

#include "glm/detail/type_mat.hpp"

namespace Engine { class World; }

namespace Renderer
{
	class Model;

	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		~GraphicsEngine();

		int Initialize();
		int Shutdown();

		void StartRendering();
		void RenderWorld(Engine::World* world);
		void EndRendering();

		// Getters
		const GraphicsCore::WindowManager& GetWindowManager() const { return m_WindowManager; }

	private:
		int InitializeGlew();
		int InitializeOpenGL();
		int InitializeLightGridCompute();

		void DrawOpaqueObjects(Engine::World* world);
		void DrawDebugLights(Engine::World * world);
		void BindViewProjMatrices(ShaderProgramId shaderProgramId, Engine::World * world);
		void DepthPrePass(Engine::World* world);
		void GridComputePass(const glm::mat4& x);
		void LightCullingPass(Engine::World* world);

		
		// todo: revisit this and maybe move it??
		void DrawModel(const Model* model);
		void DrawSkyBox(Engine::World* world);

	private:
		GraphicsCore::WindowManager m_WindowManager;
	};
}



