#pragma once

#include <map>

#include "Core/Input/KeyboardEvent.h"
#include "Core/Input/MouseEvent.h"

namespace Engine
{
	class Camera;
}

namespace Game
{
	class Player : public Core::KeyboardInputListener, public Core::MouseInputListener
	{
	public:
		Player();
		~Player();
		
		Engine::Camera* GetCamera();

		void Update();

		// Inherited via InputKeyboardListener
		virtual void OnKeyboardInputEvent(const Core::KeyboardInputEvent & event) override;
		virtual void OnMouseInputEvent(const Core::MouseInputEvent& event) override;


	private:
		Engine::Camera* m_FPCamera;

		int m_MouseX, m_MouseY;
		std::map<char, bool> m_IsKeyPressed;

	};
}
