#pragma once

#include <stdint.h>

namespace Game
{
	class WorldChunk;
	class WorldGeneration
	{
	public:
		static WorldChunk* CreateFlatChunk(uint32_t x, uint32_t y, uint32_t z);
	};
}
