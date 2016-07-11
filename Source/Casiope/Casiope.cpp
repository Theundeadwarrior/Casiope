#include "Engine\GameEngine.h"

#include "TestScene.h"

int main(int argc, char** argv)
{
	Engine::GameEngine engine;
	engine.Initialize();
	
	// Init Test Scene!!
	Casiope::InitializeTestScene(engine);



	engine.Loop();
	engine.Shutdown();
	return 0;
}