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
	// TEST SCENE

	void InitializeTestScene()
	{
		PerspectiveCameraParams params(45, 1024 / 768.0f, 0.1f, 1000.0f);
		Camera* camera = new PerspectiveCamera(params, glm::vec3(0, 5, 5), glm::vec3(0, 0, -1), glm::vec3(0, 5, -5));
		
		Core::Image<unsigned char> skyBoxImages[6];
		Core::LoadImageFromFile(skyBoxImages[0], "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxImages[1], "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxImages[2], "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxImages[3], "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxImages[4], "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxImages[5], "../../data/textures/skybox/front.bmp");
		
		//for(auto skyBoxImg : skyBoxImages)
		//{
		//	ResourceManager::GetInstance()->GetTextureManager().AddTextureFromImage(skyBoxImg, GraphicsCore::e_TexFormatRGB);
		//}

		//// Update camera parameters
		//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, &camera->GetViewMatrix(), SHADER_MATRIX44);

		//glm::mat4x4* projectionMatrix = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
		//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX, projectionMatrix, SHADER_MATRIX44);
	}

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


		// todo remove
		InitializeTestScene();
		m_Renderer.InitTestGraphics();
		// end remove


	}

	void GameEngine::Shutdown()
	{
		ResourceManager::DestroyInstance();
		m_Renderer.Shutdown();
	}

	int GameEngine::Loop()
	{
		// Loop
		while (true)
		{
			m_InputManager.Update();

			m_Renderer.Render();
		}
		return 0;
	}


}
