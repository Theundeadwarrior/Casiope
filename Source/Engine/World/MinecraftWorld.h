#pragma once

#include <list>
#include "Core/Math/Vector.h"

#define WORLD_CHUNK_WIDTH 4
#define WORLD_CHUNK_LENGHT 4
#define WORLD_CHUNK_HEIGHT 4

namespace Engine
{
	class MinecraftWorldChunk
	{
		uint8_t m_Blocks[WORLD_CHUNK_WIDTH][WORLD_CHUNK_LENGHT][WORLD_CHUNK_WIDTH];
		Vector3 m_Position;
	};

	class MinecraftWorld
	{
	public:
		MinecraftWorld();
		~MinecraftWorld();

		void InitTestWorld();

	private:
		std::list<MinecraftWorldChunk*> m_LoadedChunks;
	};

}
