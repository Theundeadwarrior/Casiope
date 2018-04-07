

#include "Core/Math/Math.h"
#include "Core/Noise/Noise.h"

#include "Game/World/WorldGeneration.h"

#include "Renderer/Model/ChunkMesh.h"
#include "Game/Chunk/WorldChunk.h"


#include <ctime>


namespace Game
{
	WorldGenerator::WorldGenerator()
	{
		m_HeightGenerator.m_Frequency = 1.0;
		m_HeightGenerator.m_Lacunarity = 1.5;
		
		std::srand(std::time(nullptr)); // use current time as seed for random generator
		m_HeightGenerator.m_Seed = rand(); // todo: remove this and have a seed 
	}


	WorldChunk* WorldGenerator::CreateFlatChunk(uint32_t x, uint32_t y, uint32_t z)
	{
		WorldChunk* chunk = new WorldChunk();
		chunk->m_Mesh = new Renderer::ChunkMesh();

		for (uint32_t x = 0; x < WORLD_CHUNK_WIDTH; ++x)
		{
			for (uint32_t y = 0; y < WORLD_CHUNK_LENGHT; ++y)
			{
				chunk->SetBlock(x, y, 0, BlockType::Stone);
			}
		}

		chunk->SetPosition(x, y, z);

		return chunk;
	}

	//float Noise1(uint32_t x, uint32_t y) {
	//	uint32_t n;
	//	n = x + y * 57;
	//	n = (n << 13) ^ n;
	//	return (1.0 - ((n * ((n * n * 15731) + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
	//}

	WorldChunk* WorldGenerator::GenerateChunk2(int32_t x, int32_t y, int32_t z)
	{
		WorldChunk* chunk = new WorldChunk();
		chunk->m_Mesh = new Renderer::ChunkMesh();

		for (uint32_t sx = 0; sx < WORLD_CHUNK_WIDTH; ++sx)
		{
			for (uint32_t sy = 0; sy < WORLD_CHUNK_LENGHT; ++sy)
			{
				// remap the value between 0 -> 1
				double value = (Core::Max(Core::Min(m_HeightGenerator.GetValue(x + sx / (double)WORLD_CHUNK_WIDTH, y + sy / (double)WORLD_CHUNK_LENGHT, 0.0), 1.0), -1.0) + 1.0) / 2.1;
				
				uint32_t valueint = floor(value * WORLD_CHUNK_HEIGHT);

				uint32_t sz = 0;
				for(sz = 0; sz <= valueint; ++sz)
					chunk->SetBlock(sx, sy, sz, BlockType::Stone);
				if (sz != 0)
				{
					chunk->SetBlock(sx, sy, sz - 1, BlockType::Grass);
				}
				chunk->SetBlock(sx, sy, sz, BlockType::Grass);
			}
		}

		chunk->SetPosition(x, z, y);

		return chunk;
	}
}
