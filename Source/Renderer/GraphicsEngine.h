#pragma once

#include "Window\WindowManager.h"

namespace Engine
{
	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		~GraphicsEngine();

		int InitializeGlew();

		int Initialize();
		int Shutdown();
		void Render();

	private:
		WindowManager m_WindowManager;
	};
}



