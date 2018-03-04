#pragma once

#include "Game/World/MinecraftWorldChunk.h"

namespace Game
{
	class WorldGeneration
	{
	public:
		static MinecraftWorldChunk* CreateFlatChunk(uint32_t x, uint32_t y, uint32_t z);
	};
}
