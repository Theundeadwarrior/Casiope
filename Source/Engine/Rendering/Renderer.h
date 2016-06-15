#pragma once

#include "Rendering\WindowManager.h"

namespace Engine
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		int InitializeGlew();

		int Initialize();
		int Shutdown();
		void Render();

	private:
		WindowManager m_WindowManager;
	};
}



