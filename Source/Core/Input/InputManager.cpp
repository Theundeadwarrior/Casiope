#include "InputManager.h"

#include <stdio.h>

#include "Core\Input\KeyboardEvent.h"
#include "Core\Input\MouseEvent.h"

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

	void InputManager::NotifyMouseListener(const MouseInputEvent& event)
	{
		for (auto* listener : m_MouseListener)
		{
			listener->OnMouseInputEvent(event);
		}
	}

	// todo : change to use SDL_GetKeyboardState instead of using the events for keyboard

	void InputManager::Update()
	{
		while (SDL_PollEvent(&m_CurrentEvent))
		{
			switch (m_CurrentEvent.type)
			{
			case SDL_KEYDOWN:
			{
				if (m_CurrentEvent.key.repeat == false)
				{
					KeyboardEventType type = KeyboardEventType::KEY_PRESSED;
					KeyboardInputEvent keyboardEvent(m_CurrentEvent.key.keysym.sym, type, 0, 0); // todo : pass in the cursor position so we can raycast from there.
					NotifyKeyboardListener(keyboardEvent);
				}
				break;
			}
			case SDL_KEYUP:
			{
				if (m_CurrentEvent.key.repeat == false)
				{
					KeyboardEventType type = KeyboardEventType::KEY_RELEASED;
					KeyboardInputEvent keyboardEvent(m_CurrentEvent.key.keysym.sym, type, 0, 0); // todo : pass in the cursor position so we can raycast from there.
					NotifyKeyboardListener(keyboardEvent);
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
				MouseInputEvent mouseEvent = MouseInputEvent(MOUSE_MOTION_ONLY, NO_CLICK, MOUSE_NO_MODIFIER, m_CurrentEvent.motion.x, m_CurrentEvent.motion.y);
				NotifyMouseListener(mouseEvent);
				break;
			}
			case SDL_QUIT:
				return;
			}


		}
	}
}
