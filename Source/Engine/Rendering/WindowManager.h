#pragma once

struct SDL_Window;
typedef void* SDL_GLContext;

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

private:
	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;

};

