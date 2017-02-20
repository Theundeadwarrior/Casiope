#include "MinecraftWorldMesh.h"

#include "GraphicsCore/Geometry/Geometry.h"

namespace Renderer
{
	MinecraftChunkMesh::MinecraftChunkMesh(unsigned int chunkSizeX, unsigned int chunkSizeY, unsigned int chunkSizeZ)
	{
		m_ChunkGeometry = new GraphicsCore::MinecraftWorldGeometry;
	}

	inline void MinecraftChunkMesh::AddBlock(uint8_t i, uint8_t j, uint8_t k, uint8_t textureValue)
	{
		m_ChunkGeometry->m_Vertex.push_back(Core::Vector3(i, j, k));
		m_ChunkGeometry->m_TextureNumber.push_back(textureValue);
	}

	inline void MinecraftChunkMesh::Reset()
	{
		m_ChunkGeometry->m_Vertex.clear();
		m_ChunkGeometry->m_TextureNumber.clear();
	}

	MinecraftChunkMesh::~MinecraftChunkMesh()
	{
		delete m_ChunkGeometry;
	}
}
