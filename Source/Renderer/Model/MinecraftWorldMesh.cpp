#include "MinecraftWorldMesh.h"

#include "Renderer/Resource/GraphicsResourceManager.h"
#include "GraphicsCore/Mesh/Mesh.h"

namespace Renderer
{
	//MinecraftChunkMesh::MinecraftChunkMesh(unsigned int chunkSizeX, unsigned int chunkSizeY, unsigned int chunkSizeZ)
	//	: m_ChunkGeometry(chunkSizeX * chunkSizeY * chunkSizeZ)
	//{
	//}

		/*m_ChunkGeometry->m_Vertex.push_back(Core::Vector4(i, j, k, textureValue));
		m_ChunkGeometry->m_Vao
		g_Mesh.m_GPUParams.m_VAO = GraphicsCore::BuildVertexBufferFromVertexArray(GraphicsCore::GeometryGPUType::V3T2, vertices, sizeof(vertices));*/
	

	void MinecraftChunkMesh::Update(void* data, uint32_t count)
	{
		if (m_GeometryId != INVALID_GEOMETRY_ID)
		{
			GraphicsResourceManager::GetInstance()->GetGeometryManager().RemoveGeometry(m_GeometryId);
		}
		m_RealGeometry.UpdateGeometry(data, count, GraphicsCore::GeometryGPUType::V3BT2B);
		m_GeometryId = GraphicsResourceManager::GetInstance()->GetGeometryManager().AddMesh(&m_RealGeometry);
	}

	void MinecraftChunkMesh::Reset()
	{
		if (m_GeometryId != INVALID_GEOMETRY_ID)
		{
			GraphicsResourceManager::GetInstance()->GetGeometryManager().RemoveGeometry(m_GeometryId);
		}
		m_GeometryId = INVALID_GEOMETRY_ID;
	}

	MinecraftChunkMesh::~MinecraftChunkMesh()
	{
	}
}
