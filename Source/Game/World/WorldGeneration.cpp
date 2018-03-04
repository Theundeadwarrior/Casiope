#include "Game/World/WorldGeneration.h"
#include "Renderer/Model/MinecraftWorldMesh.h"

namespace Game
{
	MinecraftWorldChunk* WorldGeneration::CreateFlatChunk(uint32_t x, uint32_t y, uint32_t z)
	{
		MinecraftWorldChunk* chunk = new MinecraftWorldChunk(nullptr);
		chunk->m_Mesh = new Renderer::MinecraftChunkMesh();

		for (uint32_t x = 0; x < WORLD_CHUNK_WIDTH; ++x)
		{
			for (uint32_t y = 0; y < WORLD_CHUNK_LENGHT; ++y)
			{
				chunk->SetBlock(x, y, 0, MinecraftBlockType::Stone);
			}
		}

		chunk->SetPosition(x, y, z);

		return chunk;
	}
}
