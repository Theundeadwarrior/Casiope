#include "ChunkMesh.h"

namespace Renderer
{
	void ChunkMesh::Update(void* data, uint32_t count)
	{
		UpdateGeometry(data, count, GraphicsCore::VertexBufferType::V3BT2B);
	}
}
