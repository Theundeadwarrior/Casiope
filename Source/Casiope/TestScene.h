#pragma once

#include <glm/glm.hpp>

#include "Core/File/ImageUtilities.h"

#include "GraphicsCore/Mesh/Mesh.h"

#include "Engine/GameEngine.h"
#include "Game/State/GameState.h"

namespace Casiope
{
	void InitializeTestScene(Engine::GameEngine& gameEngine, const char* imagePath)
	{
		//Core::Image<unsigned char> skyBoxImages[6];
		//Core::LoadImageFromFile(skyBoxImages[0], imagePath);
		//Core::LoadImageFromFile(skyBoxImages[1], imagePath);
		//Core::LoadImageFromFile(skyBoxImages[2], imagePath);
		//Core::LoadImageFromFile(skyBoxImages[3], imagePath);
		//Core::LoadImageFromFile(skyBoxImages[4], imagePath);
		//Core::LoadImageFromFile(skyBoxImages[5], imagePath);

		//for(auto skyBoxImg : skyBoxImages)
		//{
		//	GraphicsResourceManager::GetInstance()->GetTextureManager().AddTextureFromImage(skyBoxImg, GraphicsCore::e_TexFormatRGB);
		//}

		//// Update camera parameters
		//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::VIEWMATRIX, &camera->GetViewMatrix(), SHADER_MATRIX44);

		//glm::mat4x4* projectionMatrix = (dynamic_cast<SceneManager::PerspectiveCamera*>(camera))->GetPerspectiveMat();
		//LowLevelGraphics::ShaderProgram::UpdateGlobalShaderParameter(LowLevelGraphics::PROJECTIONMATRIX, projectionMatrix, SHADER_MATRIX44);

		//GraphicsCore::Mesh cubesGeometry;

		Game::GameState* state = new Game::GameState();
		gameEngine.PushState(state);
	}
}
