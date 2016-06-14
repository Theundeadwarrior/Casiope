#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "World\world.h"
#include "Core\Rendering\GameEngine.h"

#define CLEAR_SCREEN_STRING "\n\n\n\n\n\n\n\n\n\n"



int main(int argc, char** argv)
{
	World world(100, 30);

	Core::GameEngine renderer;
	renderer.InitWindow();

	bool gameRunning = true;
	
	std::cout << CLEAR_SCREEN_STRING;
	world.Draw();


	char currentChar;
	while (gameRunning)
	{
		currentChar = _getch();
		std::cout << CLEAR_SCREEN_STRING;
		world.Draw();
		std::cout << "Key Pressed: " << currentChar;
	}
	return 0;
}