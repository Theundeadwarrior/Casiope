#pragma once
#include <vector>

#include <SDL.h>

#include "Core/Event/Event.h"

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
		void HandleEvent(const SDL_Event & event);

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

		void GetMouseState(int& x, int& y);

		void GetResetMouseValues(int& x, int& y);
		void SetResetMouseValues(int x, int y);

		void SetResetMouseBehavior(bool resetMouse) { m_ResetMouseToPosition = resetMouse; }

		void ResetMouseToCenter();

	private:
		void NotifyKeyboardListener(const KeyboardInputEvent& event);
		void NotifyMouseListener(const MouseInputEvent & event);


	private:
		std::vector<KeyboardInputListener*> m_KeyboardListener;
		std::vector<MouseInputListener*> m_MouseListener;

		bool m_ResetMouseToPosition;
		int m_OldMousePositionX;
		int m_OldMousePositionY;
	};

}

