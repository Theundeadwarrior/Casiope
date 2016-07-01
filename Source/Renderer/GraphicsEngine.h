#pragma once

#include "GraphicsCore\Window\WindowManager.h"

namespace Renderer
{
	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		~GraphicsEngine();

		int InitializeGlew();

		// todo: remove this
		void InitTestGraphics();

		int Initialize();
		int Shutdown();
		void Render();

	private:
		GraphicsCore::WindowManager m_WindowManager;
	};
}



