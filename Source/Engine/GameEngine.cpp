#include "GameEngine.h"
#include <iostream>
#include <SDL.h>


#include "Camera\PerspectiveCamera.h"
#include "GraphicsCore\Textures\Texture.h"
#include "Renderer\SkyBox\SkyBox.h"

namespace Engine
{
	// TEST SCENE
	void InitializeTestScene()
	{
		PerspectiveCameraParams params(45, 1024 / 768.0f, 0.1f, 1000.0f);
		Camera* camera = new PerspectiveCamera(params, glm::vec3(0, 5, 5), glm::vec3(0, 0, -1), glm::vec3(0, 5, -5));

		Renderer::SkyBoxParams skyBoxParam;
		Core::LoadImageFromFile(skyBoxParam.GetImageParam(Renderer::SkyBoxFaces::e_FaceFront), "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxParam.GetImageParam(Renderer::SkyBoxFaces::e_FaceBack),  "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxParam.GetImageParam(Renderer::SkyBoxFaces::e_FaceBottom),"../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxParam.GetImageParam(Renderer::SkyBoxFaces::e_FaceLeft),  "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxParam.GetImageParam(Renderer::SkyBoxFaces::e_FaceRight), "../../data/textures/skybox/front.bmp");
		Core::LoadImageFromFile(skyBoxParam.GetImageParam(Renderer::SkyBoxFaces::e_FaceTop),   "../../data/textures/skybox/front.bmp");
		

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
		InitializeTestScene();
	}

	void GameEngine::Shutdown()
	{
		m_Renderer.Shutdown();
	}

	int GameEngine::Loop()
	{
		// Loop
		SDL_Event events;
		while (true)
		{
			SDL_WaitEvent(&events);
			if (events.window.event == SDL_WINDOWEVENT_CLOSE)
				break;

			m_Renderer.Render();
		}
		return 0;
	}


}
