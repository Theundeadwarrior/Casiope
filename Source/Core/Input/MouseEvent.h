#pragma once

#include "Core/Input/InputManager.h"

namespace Core
{
	class MouseInputEvent : public InputEvent
	{
	public:
		//KeyboardInputEvent(unsigned int keyEntered, KeyboardEventType eventType, int x, int y);

		//unsigned int m_Key;
		//KeyboardEventType m_Type;
	};

	class MouseInputListener
	{
	public:
		MouseInputListener() {}
		virtual ~MouseInputListener() {}
		virtual void OnMouseInputEvent(const MouseInputEvent& event) = 0;
	};


}
