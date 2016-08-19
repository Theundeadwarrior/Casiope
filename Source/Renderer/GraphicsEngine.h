#pragma once

#include "GraphicsCore/Window/WindowManager.h"

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

		void RenderWorld(Engine::World* world);

		// Getters
		const GraphicsCore::WindowManager& GetWindowManager() const { return m_WindowManager; }

	private:
		int InitializeGlew();
		int InitializeOpenGL();

		log4cxx::LoggerPtr m_Logger;

	private:
		GraphicsCore::WindowManager m_WindowManager;
	};
}



