#pragma once

#include <stdint.h>
#include "GraphicsCore/Mesh/Mesh.h"

namespace Renderer
{
	// TODO: this should derive from Mesh instead.
	// GPU resource wrapper. 
	class MinecraftChunkMesh : public GraphicsCore::Mesh
	{
	public:
		MinecraftChunkMesh() = default;
		~MinecraftChunkMesh() = default;

		void Update(void* data, uint32_t count);
	};
}
