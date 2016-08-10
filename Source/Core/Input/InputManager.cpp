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

	void InputManager::GetMouseState(int & x, int & y)
	{
		SDL_GetMouseState(&x, &y);
	}

	void InputManager::GetResetMouseValues(int & x, int & y)
	{
		x = m_OldMousePositionX;
		y = m_OldMousePositionY;
	}

	void InputManager::SetResetMouseValues(int x, int y)
	{
		m_OldMousePositionX = x;
		m_OldMousePositionY = y;
	}

	void InputManager::ResetMouseToCenter()
	{
		SDL_WarpMouseGlobal(m_OldMousePositionX, m_OldMousePositionY); // do not hardcode these!!
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
			case SDL_QUIT:
				return;
			}


		}
		// Mouse motion only since we cannot rely on MouseMotion events from SDL because we might reset the mouse.
		{
			int x = m_OldMousePositionX, y = m_OldMousePositionY;
			SDL_GetGlobalMouseState(&x, &y);

			if (x != m_OldMousePositionX || y != m_OldMousePositionY)
			{
				MouseInputEvent mouseEvent = MouseInputEvent(MOUSE_MOTION_ONLY, NO_CLICK, MOUSE_NO_MODIFIER, x, y, x - m_OldMousePositionX, y - m_OldMousePositionY);
				NotifyMouseListener(mouseEvent);
			}

			if (m_ResetMouseToPosition)
			{
				SDL_WarpMouseGlobal(m_OldMousePositionX, m_OldMousePositionY); // todo: change to window and not global warp
			}
			else
			{
				m_OldMousePositionX = x;
				m_OldMousePositionY = y;
			}


		}

	}
}
