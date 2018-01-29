#include "MinecraftWorldMesh.h"

namespace Renderer
{
	void MinecraftChunkMesh::Update(void* data, uint32_t count)
	{
		UpdateGeometry(data, count, GraphicsCore::VertexBufferType::V3BT2B);
	}
}
