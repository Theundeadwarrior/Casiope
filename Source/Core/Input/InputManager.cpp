#include "InputManager.h"

#include <stdio.h>

#include "Core/Input/KeyboardEvent.h"
#include "Core/Input/MouseEvent.h"

namespace Core
{
	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::RegisterKeyboardListener(KeyboardInputListener * listener)
	{
		m_KeyboardListener.push_back(listener);
	}

	void InputManager::RegisterMouseListener(MouseInputListener * listener)
	{
		m_MouseListener.push_back(listener);
	}

	void InputManager::NotifyKeyboardListener(const KeyboardInputEvent& event)
	{
		for (auto* listener : m_KeyboardListener)
		{
			listener->OnKeyboardInputEvent(event);
		}
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
