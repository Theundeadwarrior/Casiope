#include "MinecraftWorldMesh.h"

#include "GraphicsCore/Geometry/Geometry.h"

namespace Renderer
{
	//MinecraftChunkMesh::MinecraftChunkMesh(unsigned int chunkSizeX, unsigned int chunkSizeY, unsigned int chunkSizeZ)
	//	: m_ChunkGeometry(chunkSizeX * chunkSizeY * chunkSizeZ)
	//{
	//}

		/*m_ChunkGeometry->m_Vertex.push_back(Core::Vector4(i, j, k, textureValue));
		m_ChunkGeometry->m_Vao
		g_Geometry.m_GPUParams.m_VAO = GraphicsCore::BuildVertexBufferFromVertexArray(GraphicsCore::GeometryGPUType::V3T2, vertices, sizeof(vertices));*/
	

	inline void MinecraftChunkMesh::Update(void* data, uint32_t count)
	{
		m_ChunkGeometry.UpdateGeometry(data, count);
	}

	inline void MinecraftChunkMesh::Reset()
	{
		//m_ChunkGeometry->m_Vertex.clear();
	}

	MinecraftChunkMesh::~MinecraftChunkMesh()
	{
	}
}
