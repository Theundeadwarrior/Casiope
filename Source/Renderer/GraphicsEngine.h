#pragma once

#include "GraphicsCore/Window/WindowManager.h"

#include <Core/Logging/Logger.h>

namespace Engine { class World; }

namespace Renderer
{
	class Model;

	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		~GraphicsEngine();

		// todo: remove this
		void InitTestGraphics();

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

		void DrawOpaqueObjects(Engine::World* world);
		
		// todo: revisit this and maybe move it??
		void DrawModel(const Model* model);

		log4cxx::LoggerPtr m_Logger;

	private:
		GraphicsCore::WindowManager m_WindowManager;
	};
}



