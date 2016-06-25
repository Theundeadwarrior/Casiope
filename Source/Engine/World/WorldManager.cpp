#include "WorldManager.h"

Engine::WorldManager::WorldManager()
{
}

Engine::WorldManager::~WorldManager()
{
}

void Engine::WorldManager::Update()
{
	m_CurrentWorld->Update();
}

void Engine::World::Update()
{
}
