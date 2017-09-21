#pragma once

#include <stdint.h>
#include "GraphicsCore/Geometry/Geometry.h"
#include "Renderer\Mesh\Mesh.h"

namespace Renderer
{
	// GPU resource wrapper
	class MinecraftChunkMesh : public Mesh
	{
	public:
		MinecraftChunkMesh() = default;

		void Update(void* data, uint32_t count);
		void Reset();

		~MinecraftChunkMesh();

	private:
		GraphicsCore::Geometry m_RealGeometry;
	};
}


