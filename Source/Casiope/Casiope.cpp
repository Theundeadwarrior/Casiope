#include "Engine/GameEngine.h"

#include "TestScene.h"

int main(int argc, char** argv)
{
	Engine::GameEngine engine;
	engine.Initialize();

	const char* imagePath = "../../data/textures/skybox/front.bmp";
	if (argc == 2)
	{
		imagePath = argv[1];
	}

	// Init Test Scene!!
	Casiope::InitializeTestScene(engine, imagePath);

	engine.Loop();
	engine.Shutdown();
	return 0;
}
