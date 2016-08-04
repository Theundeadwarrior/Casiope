#pragma once

#include <map>

#include "Core\Input\KeyboardEvent.h"

namespace Engine
{
	class Camera;
}

namespace Game
{
	class Player : public Core::KeyboardInputListener
	{
	public:
		Player();
		~Player();
		
		Engine::Camera* GetCamera();

		void Update();

		// Inherited via InputKeyboardListener
		virtual void OnKeyboardInputEvent(const Core::KeyboardInputEvent & event) override;

	private:
		Engine::Camera* m_FPCamera;

		std::map<char, bool> m_IsKeyPressed;

	};
}
