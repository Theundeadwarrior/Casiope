#pragma once
#include <SDL.h>

#include "Core\Event\Event.h"

namespace Core
{
	class InputEvent : public Event
	{
	};



	class MouseInputEvent : InputEvent
	{

	};

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void Update();

	private:
		SDL_Event m_CurrentEvent;
	};

}

