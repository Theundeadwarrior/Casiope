#include "Core\Rendering\GameEngine.h"


int main(int argc, char** argv)
{
	Core::GameEngine engine;
	engine.InitWindow();
	engine.Loop();
	engine.ShutdownWindow();
	return 0;
}