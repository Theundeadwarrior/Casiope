#include "MinecraftWorld.h"


namespace Engine
{
	void MinecraftWorld::InitTestWorld()
	{
		// Faking some data just to make it work.
		MinecraftWorldChunk* testChunk = new MinecraftWorldChunk();

		for (uint32_t i = 0; i < WORLD_CHUNK_WIDTH; ++i)
		{
			for (uint32_t j = 0; j < WORLD_CHUNK_LENGHT; ++j)
			{
				testChunk->m_Blocks[i][j][0] = MinecraftBlockType::Grass;
			}
		}
		m_LoadedChunks.push_back(testChunk);

		testChunk->UpdateWorldChunkMesh();
	}

	MinecraftWorld::MinecraftWorld()
	{
		InitTestWorld();
	}

	MinecraftWorld::~MinecraftWorld()
	{
	}

	void MinecraftWorldChunk::UpdateWorldChunkMesh()
	{
		if (m_NeedsUpdate)
		{
			uint8_t vertices[WORLD_CHUNK_HEIGHT * WORLD_CHUNK_LENGHT * WORLD_CHUNK_WIDTH];
			uint32_t currentVertex = 0;
			m_Mesh.Reset();
			for (uint32_t i = 0; i < WORLD_CHUNK_WIDTH; ++i)
			{
				for (uint32_t j = 0; j < WORLD_CHUNK_LENGHT; ++j)
				{
					for (uint32_t k = 0; k < WORLD_CHUNK_HEIGHT; ++k)
					{
						if (m_Blocks[i][j][k] != MinecraftBlockType::Air)
						{
							vertices[currentVertex++] = i;
							vertices[currentVertex++] = j;
							vertices[currentVertex++] = k;
							vertices[currentVertex++] = static_cast<uint8_t>(m_Blocks[i][j][k]);
						}
					}
				}
			}
			m_Mesh.Update(vertices, currentVertex);
		}
	}

	inline MinecraftBlockType MinecraftWorldChunk::GetBlock(uint32_t x, uint32_t y, uint32_t z)
	{
		return m_Blocks[x][y][z];
	}

	inline void MinecraftWorldChunk::SetBlock(uint32_t x, uint32_t y, uint32_t z, MinecraftBlockType type)
	{
		if (GetBlock(x, y, z) != type)
		{
			m_Blocks[x][y][z] = type;
			m_NeedsUpdate = true;
		}
	}
}
