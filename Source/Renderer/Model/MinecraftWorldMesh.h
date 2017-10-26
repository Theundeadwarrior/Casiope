#pragma once

#include <stdint.h>
#include "GraphicsCore/Mesh/Mesh.h"
#include "Renderer/Model/Model.h"

namespace Renderer
{
	// TODO: this should derive from Mesh instead.
	// GPU resource wrapper. 
	class MinecraftChunkMesh : public Model
	{
	public:
		MinecraftChunkMesh() = default;

		void Update(void* data, uint32_t count);
		void Reset();

		~MinecraftChunkMesh();

	private:
		GraphicsCore::Mesh m_RealGeometry;
	};
}


