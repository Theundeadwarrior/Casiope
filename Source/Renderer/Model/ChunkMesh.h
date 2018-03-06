#pragma once

#include <stdint.h>
#include "GraphicsCore/Mesh/Mesh.h"

namespace Renderer
{
	// GPU resource wrapper. 
	class ChunkMesh : public GraphicsCore::Mesh
	{
	public:
		ChunkMesh() = default;
		~ChunkMesh() = default;

		void Update(void* data, uint32_t count);
	};
}
