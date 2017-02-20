#include "MinecraftWorld.h"


namespace Engine
{
	void MinecraftWorld::InitTestWorld()
	{
		// Faking some data just to make it work.
		MinecraftWorldChunk* testChunk = new MinecraftWorldChunk();
		testChunk->m_Blocks[0][0][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[0][1][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[0][2][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[0][3][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[1][0][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[1][1][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[1][2][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[1][3][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[2][0][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[2][1][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[2][2][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[2][3][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[3][0][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[3][1][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[3][2][0] = MinecraftBlockType::Grass;
		testChunk->m_Blocks[3][3][0] = MinecraftBlockType::Grass;
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
		m_Mesh.Reset();
		for (uint32_t i = 0; i < WORLD_CHUNK_WIDTH; ++i)
		{
			for (uint32_t j = 0; j < WORLD_CHUNK_LENGHT; ++j)
			{
				for (uint32_t k = 0; k < WORLD_CHUNK_HEIGHT; ++k)
				{
					m_Mesh.AddBlock(i, j, k, static_cast<uint8_t>(m_Blocks[i][j][k]));
				}
			}
		}
	}
}
