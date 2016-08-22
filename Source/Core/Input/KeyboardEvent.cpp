#include "InputManager.h"
#include "KeyboardEvent.h"

namespace Core
{
	KeyboardInputEvent::KeyboardInputEvent(unsigned int keyEntered, KeyboardEventType eventType, int /*x*/, int /*y*/)
		: m_Key(keyEntered)
		, m_Type(eventType)
	{
	}

}
