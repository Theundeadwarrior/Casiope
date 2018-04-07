#pragma once

#include <stdint.h>

namespace Core
{
	class PerlinNoise;
}

namespace Game
{
	class WorldChunk;

	class WorldGenerator
	{
	public:
		WorldGenerator();

		WorldChunk* CreateFlatChunk(uint32_t x, uint32_t y, uint32_t z);
		WorldChunk* GenerateChunk2(int32_t x, int32_t y, int32_t z);

	private:
		Core::PerlinNoise m_HeightGenerator;
	};
}
