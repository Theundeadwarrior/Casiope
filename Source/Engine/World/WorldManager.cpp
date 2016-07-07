#include "WorldManager.h"

#include "Engine\Camera\PerspectiveCamera.h"

namespace Engine
{
	WorldManager::WorldManager()
		: m_CurrentWorld(nullptr)
	{
	}

	WorldManager::~WorldManager()
	{
	}

	void WorldManager::Update()
	{
		m_CurrentWorld->Update();
	}

	World::World()
	{
		PerspectiveCameraParams camParams(45, 1280 / 720.f, 0.1f, 1000.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

		m_Camera = new PerspectiveCamera(camParams, cameraPos, cameraTarget, up);
	}

	void World::Update()
	{
	}

}
