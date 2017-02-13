#pragma once

#include <list>
#include "Core/Math/Vector.h"

#define WORLD_CHUNK_WIDTH 4
#define WORLD_CHUNK_LENGHT 4
#define WORLD_CHUNK_HEIGHT 4

namespace Engine
{
	enum class MinecraftBlockType : uint8_t
	{
		Grass = 1,
		Dirt,
		Stone,
		Water,

		Air = 0
	};

	class MinecraftWorldChunk
	{
	public:
		MinecraftBlockType m_Blocks[WORLD_CHUNK_WIDTH][WORLD_CHUNK_LENGHT][WORLD_CHUNK_WIDTH];
		Vector3 m_Position = { 0, 0, 0 };
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
