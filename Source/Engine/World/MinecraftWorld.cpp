#include "MinecraftWorld.h"


namespace Engine
{
	void MinecraftWorld::InitTestWorld()
	{
		MinecraftWorldChunk* testChunk = new MinecraftWorldChunk();
		m_LoadedChunks.push_back(testChunk);
	}

	MinecraftWorld::MinecraftWorld()
	{
		InitTestWorld();

	}

	MinecraftWorld::~MinecraftWorld()
	{
	}
}
