#include "GraphicsCore/Window/WindowManager.h"

#include "Core/Logging/Logger.h"

#if USING(WINDOW_MANAGER_SDL)
#include <SDL.h>
#include <SDL_opengl.h>
#elif USING(WINDOW_MANAGER_GLFW)
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <assert.h>

namespace GraphicsCore
{
    int Window::Initialize(uint32_t sizeX, uint32_t sizeY)
    {
        assert(m_IsInitialized == false);
        // Todo: Move initialization of SDL / GLFW somewhere else.
#if USING(WINDOW_MANAGER_SDL)
        // Initialisation de la SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            CORE_LOG()->error("Error when initializing SDL: {}", SDL_GetError());
            SDL_Quit();
            return -1;
        }

        // Version d'OpenGL
#ifdef _LINUX_
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
#endif

        // Double Buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        m_Window = SDL_CreateWindow("Casiope", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        if (m_Window == nullptr)
        {
            CORE_LOG()->error("Error when creating SDL Window: {}", SDL_GetError());
            SDL_Quit();
            return -1;
        }

        m_GLContext = SDL_GL_CreateContext(m_Window);

        if (m_GLContext == NULL)
        {
            CORE_LOG()->error("Error when creating SDL context: {}", SDL_GetError());
            SDL_DestroyWindow(m_Window);
            SDL_Quit();

            return -1;
        }

        SDL_ShowCursor(0);
#elif USING(WINDOW_MANAGER_GLFW)
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_Window = glfwCreateWindow(sizeX, sizeY, "Vulkan", nullptr, nullptr);
        //glfwSetWindowUserPointer(m_Window, this);
        //glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);
#endif
        m_IsInitialized = true;
        return 0;
    }

    void Window::Destroy()
    {
        assert(m_IsInitialized == true);
#if USING(WINDOW_MANAGER_SDL)
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
#elif USING(WINDOW_MANAGER_GLFW)
        glfwDestroyWindow(m_Window);
        glfwTerminate();
#endif
        m_IsInitialized = false;
    }

    void Window::Swap()
    {
#if USING(WINDOW_MANAGER_SDL)
        SDL_GL_SwapWindow(m_Window);
#elif USING(WINDOW_MANAGER_GLFW)
#endif
    }

    int WindowManager::CreateNewWindow(uint32_t sizeX, uint32_t sizeY)
    {
        return m_Window.Initialize(sizeX, sizeY);
    }

    void WindowManager::SwapCurrentWindow()
    {
        m_Window.Swap();
    }

    void WindowManager::GetCurrentWindowSize(unsigned int& o_x, unsigned int& o_y) const
    {
        assert(false, "not implemented");
        //GLint m_viewport[4];
        //glGetIntegerv(GL_VIEWPORT, m_viewport);
        //o_x = m_viewport[2];
        //o_y = m_viewport[3];
    }

    int WindowManager::ShutdownWindow()
    {
        m_Window.Destroy();
        return 0;
    }

}

