#include <Core/Logging/Logger.h>
#include <Engine/GameEngine.h>

#include "TestScene.h"


int main(int argc, char** argv)
{
	core::Logger::CreateInstance();
	core::Logger::GetInstance()->Initialize();

	Engine::GameEngine::CreateInstance();
	Engine::GameEngine::GetInstance()->Initialize();

	const char* imagePath = "../../../data/textures/skybox/front.bmp";
	if (argc == 2)
	{
		imagePath = argv[1];
	}

	// Init Test Scene!!
	Casiope::InitializeTestScene(*Engine::GameEngine::GetInstance(), imagePath);

	Engine::GameEngine::GetInstance()->Loop();
	Engine::GameEngine::GetInstance()->Shutdown();

	return 0;
}
