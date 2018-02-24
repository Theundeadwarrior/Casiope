#include "Game/World/MinecraftWorldChunk.h"

#include "GraphicsCore/Mesh/Mesh.h"

namespace Game
{
	MinecraftWorldChunk::~MinecraftWorldChunk()
	{
		delete m_Mesh;
	}

	void MinecraftWorldChunk::UpdateWorldChunkMesh()
	{
		struct Byte5Data
		{
			Byte5Data() {};
			Byte5Data(int8_t x1, int8_t x2, int8_t x3, int8_t x4, int8_t x5)
				: m_x1(x1)
				, m_x2(x2)
				, m_x3(x3)
				, m_x4(x4)
				, m_x5(x5)
			{}

			int8_t m_x1, m_x2, m_x3, m_x4, m_x5;
		};

		if (m_NeedsUpdate)
		{
			Byte5Data vertices[WORLD_CHUNK_HEIGHT * WORLD_CHUNK_WIDTH * WORLD_CHUNK_LENGHT * 6 * 6];
			uint32_t currentVertex = 0;
			for (uint32_t i = 0; i < WORLD_CHUNK_WIDTH; ++i)
			{
				for (uint32_t j = 0; j < WORLD_CHUNK_LENGHT; ++j)
				{
					for (uint32_t k = 0; k < WORLD_CHUNK_HEIGHT; ++k)
					{
						if (m_Blocks[i][k][j] != MinecraftBlockType::Air)
						{
							vertices[currentVertex++] = Byte5Data(i, j, k, 1, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k, 0, 0);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k, 1, 0);

							vertices[currentVertex++] = Byte5Data(i, j, k + 1, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k + 1, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, 0, 1);

							vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 0);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 0);
							vertices[currentVertex++] = Byte5Data(i, j, k + 1, 1, 0);

							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k, 1, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k, 1, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 0, 1);

							// Last 2 are bottom and top!!
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i, j, k + 1, 0, 0);

							vertices[currentVertex++] = Byte5Data(i, j + 1, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k, 0, 1);
						}
					}
				}
			}
			m_Mesh->UpdateGeometry(vertices, currentVertex * 5, GraphicsCore::VertexBufferType::V3BT2B);
		}
	}

	inline MinecraftBlockType MinecraftWorldChunk::GetBlock(uint32_t x, uint32_t y, uint32_t z)
	{
		return m_Blocks[x][y][z];
	}

	inline void MinecraftWorldChunk::SetBlock(uint32_t x, uint32_t y, uint32_t z, MinecraftBlockType type)
	{
		if (GetBlock(x, y, z) != type)
		{
			m_Blocks[x][y][z] = type;
			m_NeedsUpdate = true;
		}
	}
}