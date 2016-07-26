#pragma once

#include <glm\glm.hpp>

#include "Core\File\ImageUtilities.h"

#include "Engine\GameEngine.h"
#include "Engine\Camera\PerspectiveCamera.h"
#include "Game\World\GameWorld.h"

namespace Casiope
{
	void InitializeTestScene(Engine::GameEngine& gameEngine)
	{
		Engine::PerspectiveCameraParams params(45, 1024 / 768.0f, 0.1f, 1000.0f);
		Engine::Camera* camera = new Engine::PerspectiveCamera(params, glm::vec3(0, 5, 5), glm::vec3(0, 0, -1), glm::vec3(0, 5, -5));

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

		Engine::WorldManager& worldManager = gameEngine.GetWorldManager();

		Game::GameWorld* world = new Game::GameWorld();
		world->SetCurrentPlayer(new Game::Player());
		worldManager.SetCurrentWorld(world);
		gameEngine.GetGraphicsEngine().InitTestGraphics();

	}
}