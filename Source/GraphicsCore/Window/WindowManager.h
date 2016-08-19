#pragma once

#include <Core\Logging\Logger.h>

struct SDL_Window;
typedef void* SDL_GLContext;

namespace GraphicsCore
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		int InitWindow();
		int ShutdownWindow();

		SDL_Window* GetCurrentWindow()
		{
			return m_Window;
		}

		void GetCurrentWindowSize(unsigned int& o_x, unsigned int& o_y) const;

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;

		log4cxx::LoggerPtr m_Logger;

	};

}

