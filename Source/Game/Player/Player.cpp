#include "Player.h"

#include "Engine/Camera/PerspectiveCamera.h"
#include "Engine/GameEngine.h"

#include "glm/glm.hpp"

namespace Game
{
	Player::Player()
	{
		Engine::PerspectiveCameraParams camParams(45, 1280 / 720.f, 0.1f, 1000.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

		m_FPCamera = new Engine::PerspectiveCamera(camParams, cameraPos, cameraTarget, up);

		Engine::GameEngine::GetInstance()->GetInputManager().RegisterKeyboardListener(this);
	}

	Player::~Player()
	{
		Engine::GameEngine::GetInstance()->GetInputManager().UnregisterKeyboardListener(this);
	}

	Engine::Camera * Player::GetCamera()
	{
		return m_FPCamera;
	}

	void Player::Update()
	{
		static const float speed = 0.001f;
		if (m_IsKeyPressed['w'])
		{
			glm::vec3 offset =  speed * m_FPCamera->GetLookAt();
			m_FPCamera->m_position += offset;
			m_FPCamera->m_POI += offset;
		}
		if (m_IsKeyPressed['s'])
		{
			glm::vec3 offset = speed * m_FPCamera->GetLookAt();
			m_FPCamera->m_position -= offset;
			m_FPCamera->m_POI -= offset;
		}
		if (m_IsKeyPressed['a'])
		{
			glm::vec3 offset = speed * glm::normalize(glm::cross(m_FPCamera->GetLookAt(), m_FPCamera->GetUp()));
			m_FPCamera->m_position -= offset;
			m_FPCamera->m_POI -= offset;
		}
		if (m_IsKeyPressed['d'])
		{
			glm::vec3 offset = speed * glm::normalize(glm::cross(m_FPCamera->GetLookAt(), m_FPCamera->GetUp()));
			m_FPCamera->m_position += offset;
			m_FPCamera->m_POI += offset;
		}
	}

	void Player::OnKeyboardInputEvent(const Core::KeyboardInputEvent & event)
	{
		if (event.m_Type == Core::KeyboardEventType::KEY_PRESSED)
		{
			m_IsKeyPressed[event.m_Key] = true;
			printf("pressed\n");
		}
		else if (event.m_Type == Core::KeyboardEventType::KEY_RELEASED)
		{
			m_IsKeyPressed[event.m_Key] = false;
			printf("unpressed\n");
		}
	}
}
