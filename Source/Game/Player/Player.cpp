#include "Player.h"
#include "Engine\Camera\PerspectiveCamera.h"

namespace Game
{
	Player::Player()
	{
		Engine::PerspectiveCameraParams camParams(45, 1280 / 720.f, 0.1f, 1000.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

		m_FPCamera = new Engine::PerspectiveCamera(camParams, cameraPos, cameraTarget, up);
	}

	Player::~Player()
	{
	}

	Engine::Camera * Player::GetCamera()
	{
		return m_FPCamera;
	}

	void Player::Update()
	{
		if (m_IsKeyPressed['w'])
		{
			m_FPCamera->SetPosition(m_FPCamera->GetPosition() + 0.1f * m_FPCamera->GetLookAt());
		}
	}

	void Player::OnKeyboardInputEvent(const Core::KeyboardInputEvent & event)
	{
		if (event.m_Type == Core::KeyboardEventType::KEY_PRESSED)
		{
			m_IsKeyPressed[event.m_Key] = true;
		}
		else if (event.m_Type == Core::KeyboardEventType::KEY_RELEASED)
		{
			m_IsKeyPressed[event.m_Key] = false;
		}
	}
}
