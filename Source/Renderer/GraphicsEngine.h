#pragma once

#include "GraphicsCore\Window\WindowManager.h"

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
		void RenderTestScene();

		void RenderWorld(Engine::World* world);

		// Getters
		const GraphicsCore::WindowManager& GetWindowManager() const { return m_WindowManager; }



	private:
		int InitializeGlew();

	private:
		GraphicsCore::WindowManager m_WindowManager;
	};
}



