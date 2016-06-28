#include "InputManager.h"

#include <stdio.h>

#include "Input\KeyboardEvent.h"

namespace Core
{
	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::Update()
	{
		while (SDL_PollEvent(&m_CurrentEvent))
		{
			switch (m_CurrentEvent.type)
			{
			case SDL_KEYDOWN:
			{
				KeyboardEventType type = KeyboardEventType::KEY_PRESSED;
				printf("test");

			}
			case SDL_KEYUP:
			{
				KeyboardEventType type = KeyboardEventType::KEY_RELEASED;

			}
			case SDL_QUIT:
				return;
			}


		}
	}
}
