#pragma once

#include <stdint.h>
#include "GraphicsCore/Geometry/Geometry.h"

namespace Renderer
{
	// GPU resource wrapper
	class MinecraftChunkMesh
	{
	public:
		//MinecraftChunkMesh(unsigned int chunkSizeX, unsigned int chunkSizeY, unsigned int chunkSizeZ);

		void Update(void* data, uint32_t count);
		void Reset();

		~MinecraftChunkMesh();

	private:
		GraphicsCore::MinecraftChunkGeometry m_ChunkGeometry; // maybe we should have this not as a pointer!!
	};
}


