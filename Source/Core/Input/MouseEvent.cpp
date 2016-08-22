#include "Core/Input/InputManager.h"
#include "Core/Input/MouseEvent.h"

namespace Core
{
	MouseInputEvent::MouseInputEvent(MouseEventType eventType, MouseClick clickType, MouseModifier modifier, int x, int y, int relx, int rely)
		: m_EventType(eventType)
		, m_ClickType(clickType)
		, m_Modifier(modifier)
		, m_PosX(x)
		, m_PosY(y)
		, m_RelativeX(relx)
		, m_RelativeY(rely)
	{
	}
}
