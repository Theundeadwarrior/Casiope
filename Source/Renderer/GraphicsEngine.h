#pragma once

#include "GraphicsCore/Window/WindowManager.h"

#include "Renderer/Resource/GraphicsResourceManager.h"

#include <Core/Logging/Logger.h>

namespace Engine { class World; }

namespace Renderer
{
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
		const GraphicsResourceManager& GetResourceManager() const { return m_ResourceManager; }

	private:
		int InitializeGlew();
		int InitializeOpenGL();

		log4cxx::LoggerPtr m_Logger;

	private:
		GraphicsCore::WindowManager m_WindowManager;
		GraphicsResourceManager m_ResourceManager;
	};
}



