#pragma once

#include "GraphicsCore\Window\WindowManager.h"

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
		void Render();

		// Getters
		const GraphicsCore::WindowManager& GetWindowManager() const { return m_WindowManager; }



	private:
		int InitializeGlew();

	private:
		GraphicsCore::WindowManager m_WindowManager;
	};
}



