#pragma once

struct SDL_Window;
typedef void* SDL_GLContext;

namespace Core
{
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		int InitWindow();
		int Loop();
		int ShutdownWindow();

	private:
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
	};

}

