#pragma once

#include <Core/Core.h>
#include <Core/Logging/Logger.h>

#include <stdint.h>


#if USING(WINDOW_MANAGER_SDL)
struct SDL_Window;
typedef void* SDL_GLContext;
#elif USING(WINDOW_MANAGER_GLFW)
struct GLFWwindow;
#endif

namespace GraphicsCore
{
    // todo: abstract this
    class Window
    {
    public:
        int Initialize(uint32_t sizeX, uint32_t sizeY);
        void Destroy();

        void Swap();

    private:
#if USING(WINDOW_MANAGER_SDL)
        SDL_GLContext m_GLContext;
        SDL_Window* m_Window;
#elif USING(WINDOW_MANAGER_GLFW)
        GLFWwindow* m_Window;
#endif
        bool m_IsInitialized = false;
    };

    class WindowManager
    {
    public:
        int CreateNewWindow(uint32_t sizeX, uint32_t sizeY);
        int ShutdownWindow();

        void SwapCurrentWindow();

        void GetCurrentWindowSize(unsigned int& o_x, unsigned int& o_y) const;

    private:
        Window m_Window;
    };

}

