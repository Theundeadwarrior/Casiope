#pragma once

#include <map>

#include "Core/Input/KeyboardEvent.h"
#include "Core/Input/MouseEvent.h"

#include "glm/vec3.hpp"

namespace Engine
{
	class PerspectiveCamera;
}

namespace Game
{
	class Player : public Core::KeyboardInputListener, public Core::MouseInputListener
	{
	public:
		Player();
		~Player();
		
		glm::vec3 GetPosition() const;
		Engine::PerspectiveCamera* GetCamera();

		void Update();

		// Inherited via InputKeyboardListener
		virtual void OnKeyboardInputEvent(const Core::KeyboardInputEvent & event) override;
		virtual void OnMouseInputEvent(const Core::MouseInputEvent& event) override;


	private:
		Engine::PerspectiveCamera* m_FPCamera;

		int m_MouseX, m_MouseY;
		std::map<char, bool> m_IsKeyPressed;

	};
}
