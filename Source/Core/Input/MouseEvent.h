#pragma once

#include "Core\Input\InputManager.h"

namespace Core
{
	enum MouseEventType {
		MOUSE_MOTION_ONLY = 0,
		MOUSE_UP,
		MOUSE_DOWN,
		SCROLL_UP,
		SCROLL_DOWN
	};

	enum MouseClick {
		NO_CLICK = 0,
		LEFT_CLICK,
		RIGHT_CLICK,
		MIDDLE_CLICK
	};

	enum MouseModifier {
		MOUSE_NO_MODIFIER = 0,
		MOUSE_ACTIVE_SHIFT,
		MOUSE_ACTIVE_ALT,
		MOUSE_ACTIVE_CTRL
	};

	class MouseInputEvent : public InputEvent
	{
	public:
		MouseInputEvent(MouseEventType eventType, MouseClick clickType, MouseModifier modifier, int x, int y);
	
		MouseEventType m_EventType;
		MouseClick m_ClickType;
		MouseModifier m_Modifier;
		int m_PosX, m_PosY;
	};

	class MouseInputListener
	{
	public:
		MouseInputListener() {}
		virtual ~MouseInputListener() {}
		virtual void OnMouseInputEvent(const MouseInputEvent& event) = 0;
	};


}
