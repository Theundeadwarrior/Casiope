#pragma once

#include <stdint.h>

namespace GraphicsCore { class MinecraftWorldGeometry; }

namespace Renderer
{
	class MinecraftChunkMesh
	{
	public:
		MinecraftChunkMesh(unsigned int chunkSizeX, unsigned int chunkSizeY, unsigned int chunkSizeZ);


		void AddBlock(uint8_t i, uint8_t j, uint8_t k, uint8_t textureValue);

		void Reset();

		~MinecraftChunkMesh();

	private:
		GraphicsCore::MinecraftWorldGeometry* m_ChunkGeometry; // maybe we should have this not as a pointer!!
	};
}


