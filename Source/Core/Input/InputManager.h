#pragma once
#include <vector>

#include <SDL.h>

#include "Core\Event\Event.h"

namespace Core
{
	class KeyboardInputEvent;
	class KeyboardInputListener;
	class MouseInputEvent;
	class MouseInputListener;

	class InputEvent : public Event
	{
	};

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void Update();

		void RegisterKeyboardListener(KeyboardInputListener* listener);
		void UnregisterKeyboardListener(KeyboardInputListener* listener)
		{
			// todo
		}
		void RegisterMouseListener(MouseInputListener* listener);
		void UnregisterMouseListener(MouseInputListener* listener)
		{
			// todo
		}

	private:
		void NotifyKeyboardListener(const KeyboardInputEvent& event);

	private:
		std::vector<KeyboardInputListener*> m_KeyboardListener;
		std::vector<MouseInputListener*> m_MouseListener;
		SDL_Event m_CurrentEvent;
	};

}

