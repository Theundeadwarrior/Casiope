#pragma once

#include <Core/Logging/Logger.h>

#include <stdint.h>

struct SDL_Window;
typedef void* SDL_GLContext;

namespace GraphicsCore
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		int InitWindow(uint32_t sizeX, uint32_t sizeY);
		int ShutdownWindow();

		void SwapCurrentWindow();

		SDL_Window* GetCurrentWindow()
		{
			return m_Window;
		}

		void GetCurrentWindowSize(unsigned int& o_x, unsigned int& o_y) const;

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
	};

}

