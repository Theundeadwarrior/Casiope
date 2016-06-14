#pragma once

struct SDL_Window;

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
	};

}

