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

	}

	void World::Update()
	{
	}

}
