#include "Engine\GameEngine.h"

#include "TestScene.h"

int main(int argc, char** argv)
{
	Engine::GameEngine::CreateInstance();
	Engine::GameEngine::GetInstance()->Initialize();
	
	// Init Test Scene!!
	Casiope::InitializeTestScene(*Engine::GameEngine::GetInstance());

	Engine::GameEngine::GetInstance()->Loop();
	Engine::GameEngine::GetInstance()->Shutdown();
	return 0;
}