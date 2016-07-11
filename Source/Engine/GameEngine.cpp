#include "GameEngine.h"
#include <iostream>
#include <SDL.h>


#include "Camera\PerspectiveCamera.h"
#include "GraphicsCore\Textures\Texture.h"
#include "Renderer\SkyBox\SkyBox.h"
#include "Core\File\ImageUtilities.h"

#include "Engine\Resource\ResourceManager.h"


namespace Engine
{
	GameEngine::GameEngine()
	{
		
	}

	GameEngine::~GameEngine()
	{
	}

	void GameEngine::Initialize()
	{
		m_Renderer.Initialize();
		ResourceManager::CreateInstance();
	}

	void GameEngine::Shutdown()
	{
		// todo remove
		World* world = m_WorldManager.GetCurrentWorld();
		m_WorldManager.SetCurrentWorld(nullptr);
		delete world;
		// endtodo

		ResourceManager::DestroyInstance();
		m_Renderer.Shutdown();
	}

	int GameEngine::Loop()
	{
		// Loop
		while (true)
		{
			m_InputManager.Update();
			m_WorldManager.Update();

			m_Renderer.RenderWorld(m_WorldManager.GetCurrentWorld()); // TODO lcharbonneau: We shouldn't the entire world!
		}
		return 0;
	}


}
