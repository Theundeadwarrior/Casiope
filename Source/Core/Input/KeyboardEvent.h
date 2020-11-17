#pragma once

#include "Core/Input/InputManager.h"

namespace Core
{
	enum KeyboardEventType 
	{
		KEY_PRESSED = 0,
		KEY_RELEASED,
	};

	enum KeyboardSpecialKey 
	{
		KEY_NO_SPECIAL = 256,
		KEY_UP,
		KEY_DOWN,
		KEY_RIGHT,
		KEY_LEFT
	};

	class KeyboardInputEvent : public InputEvent
	{
	public:
		KeyboardInputEvent(unsigned int keyEntered, KeyboardEventType eventType, int x, int y);

		unsigned int m_Key;
		KeyboardEventType m_Type;
	};

	class KeyboardInputListener
	{
	public:
		KeyboardInputListener() {}
		virtual ~KeyboardInputListener() {}
		virtual void OnKeyboardInputEvent(const KeyboardInputEvent& event) = 0;
	};
}
