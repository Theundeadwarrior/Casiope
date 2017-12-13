#include "MinecraftWorldMesh.h"

namespace Renderer
{
	void MinecraftChunkMesh::Update(void* data, uint32_t count)
	{
		UpdateGeometry(data, count, GraphicsCore::GeometryGPUType::V3BT2B);
	}
}
