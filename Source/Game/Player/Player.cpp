#include "Player.h"

#include "Engine/Camera/PerspectiveCamera.h"
#include "Engine/GameEngine.h"
#include "Game/Chunk/WorldChunk.h"


#include "glm/glm.hpp"

namespace Game
{
	Player::Player()
	{
		Engine::PerspectiveCameraParams camParams(45, 1280 / 720.f, 0.1f, 1000.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraTarget = glm::vec3(1.0f, 0.0f, 0.0f);

		m_FPCamera = new Engine::PerspectiveCamera(camParams, cameraPos, cameraTarget, up);

		Engine::GameEngine::GetInstance()->GetInputManager().RegisterKeyboardListener(this);
		Engine::GameEngine::GetInstance()->GetInputManager().RegisterMouseListener(this);
	}

	Player::~Player()
	{
		Engine::GameEngine::GetInstance()->GetInputManager().UnregisterMouseListener(this);
		Engine::GameEngine::GetInstance()->GetInputManager().UnregisterKeyboardListener(this);

		delete m_FPCamera;
	}

	glm::vec3 Player::GetPosition() const { return m_FPCamera->GetPosition(); }

	Engine::PerspectiveCamera * Player::GetCamera()
	{
		return m_FPCamera;
	}

	void Player::Update()
	{
		static const float movementSpeed = 0.5f; // todo, use the frameTime passed by parameter!
		static const float rotationSpeed = 0.2f; // todo, use the frameTime passed by parameter!


		if (m_IsKeyPressed['w'])
		{
			glm::vec3 offset =  movementSpeed * m_FPCamera->GetForward();
			m_FPCamera->m_Position += offset;
		}
		if (m_IsKeyPressed['s'])
		{
			glm::vec3 offset = movementSpeed * m_FPCamera->GetForward();
			m_FPCamera->m_Position -= offset;
		}
		if (m_IsKeyPressed['a'])
		{
			glm::vec3 offset = movementSpeed * m_FPCamera->GetRight();
			m_FPCamera->m_Position -= offset;
		}
		if (m_IsKeyPressed['d'])
		{
			glm::vec3 offset = movementSpeed * m_FPCamera->GetRight();
			m_FPCamera->m_Position += offset;
		}

		// todo: change this so that we can place a block with the mouse button and also where we are aiming.
		if (m_IsKeyPressed['1'])
		{
			//auto* models = Engine::GameEngine::GetInstance()->GetWorldManager().GetCurrentWorld()->GetModels();
			//static_cast<WorldChunk*>((*models).front())->SetBlock(3, 3, 3, Game::MinecraftBlockType::Stone);
			//static_cast<WorldChunk*>((*models).front())->SetBlock(3, 2, 3, Game::MinecraftBlockType::Stone);
			//static_cast<WorldChunk*>((*models).front())->SetBlock(3, 1, 3, Game::MinecraftBlockType::Stone);
			//static_cast<WorldChunk*>((*models).front())->SetBlock(3, 0, 3, Game::MinecraftBlockType::Stone);
			//static_cast<WorldChunk*>((*models).front())->SetBlock(3, 4, 3, Game::MinecraftBlockType::Stone);
		}

		if (m_MouseX != 0 || m_MouseY != 0)
		{
			float yaw = m_MouseX * rotationSpeed;
			float pitch = -m_MouseY * rotationSpeed;
			m_MouseX = 0;
			m_MouseY = 0;

			m_FPCamera->SetRelativeOrientation(pitch, yaw, 0);
		}

		m_FPCamera->UpdateViewMatrix();
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

	void Player::OnMouseInputEvent(const Core::MouseInputEvent & event)
	{
		if (event.m_EventType == Core::MouseEventType::MOUSE_MOTION_ONLY)
		{
			m_MouseX = event.m_RelativeX;
			m_MouseY = event.m_RelativeY;
		}
	}
}
