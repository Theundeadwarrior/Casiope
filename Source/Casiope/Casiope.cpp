#include "Engine\GameEngine.h"


int main(int argc, char** argv)
{
	Engine::GameEngine engine;
	engine.Initialize();
	engine.Loop();
	engine.Shutdown();
	return 0;
}