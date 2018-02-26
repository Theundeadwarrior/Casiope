#include "Game/World/MinecraftWorldChunk.h"

#include "GraphicsCore/Mesh/Mesh.h"

namespace Game
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


	MinecraftWorldChunk::~MinecraftWorldChunk()
	{
		delete m_Mesh;
	}

	void MinecraftWorldChunk::UpdateWorldChunkMesh()
	{
		if (m_NeedsUpdate)
		{
			Byte5Data vertices[WORLD_CHUNK_HEIGHT * WORLD_CHUNK_WIDTH * WORLD_CHUNK_LENGHT * 6 * 6 / 2];
			uint32_t currentVertex = 0;
			for (uint32_t i = 0; i < WORLD_CHUNK_WIDTH; ++i)
			{
				for (uint32_t j = 0; j < WORLD_CHUNK_HEIGHT; ++j)
				{
					for (uint32_t k = 0; k < WORLD_CHUNK_LENGHT; ++k)
					{
						if (m_Blocks[i][k][j] != MinecraftBlockType::Air)
						{
							currentVertex += BuildBlockVertices(&vertices[currentVertex], i, j, k);
						}
					}
				}
			}
			m_Mesh->UpdateGeometry(vertices, currentVertex * 5, GraphicsCore::VertexBufferType::V3BT2B);
		}
	}

	MinecraftBlockType MinecraftWorldChunk::GetBlock(uint32_t x, uint32_t y, uint32_t z) const
	{
		return m_Blocks[x][y][z];
	}

	void MinecraftWorldChunk::SetBlock(uint32_t x, uint32_t y, uint32_t z, MinecraftBlockType type)
	{
		if (GetBlock(x, y, z) != type)
		{
			m_Blocks[x][y][z] = type;
			m_NeedsUpdate = true;
		}
	}

	const uint8_t* MinecraftWorldChunk::GetTexOffsets(MinecraftBlockType type, MinecraftBlockOrientation face, MinecraftBlockOrientation orientation)
	{
		MinecraftBlockFace realFace;
		if (face == MinecraftBlockOrientation::North)
			realFace = MinecraftBlockFace::Front;
		else if (face == MinecraftBlockOrientation::South)
			realFace = MinecraftBlockFace::Back;
		else if (face == MinecraftBlockOrientation::East)
			realFace = MinecraftBlockFace::Left;
		else if (face == MinecraftBlockOrientation::West)
			realFace = MinecraftBlockFace::Right;
		else if (face == MinecraftBlockOrientation::Up)
			realFace = MinecraftBlockFace::Top;
		else if (face == MinecraftBlockOrientation::Down)
			realFace = MinecraftBlockFace::Bottom;
		
		return m_BlockDataBase->GetTextureOffsets(type, realFace);
	}

	uint32_t MinecraftWorldChunk::BuildBlockVertices(Byte5Data* vertices, uint32_t i, uint32_t j, uint32_t k)
	{
		uint32_t currentVertex = 0;
		MinecraftBlockType type = m_Blocks[i][k][j];

		// Need some data to tell us what direction the block is facing...
		const MinecraftBlockOrientation orientation = MinecraftBlockOrientation::North;
		
		// West face
		if (k == 0 || m_Blocks[i][k - 1][j] == MinecraftBlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, MinecraftBlockOrientation::West, orientation);
			//glm::ivec2 texOffset = GetFrontTexOffset(GetBlock(i,j,k), MinecraftBlockOrientation::West, orientation);
			vertices[currentVertex++] = Byte5Data(i, j, k, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i, j, k, texOffsets[0] + 1, texOffsets[1] + 0);
		}

		if (k == WORLD_CHUNK_LENGHT - 1 || m_Blocks[i][k + 1][j] == MinecraftBlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, MinecraftBlockOrientation::East, orientation);
			vertices[currentVertex++] = Byte5Data(i, j, k + 1, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i, j, k + 1, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, texOffsets[0], texOffsets[1] + 1);
		}

		if (i == 0 || m_Blocks[i - 1][k][j] == MinecraftBlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, MinecraftBlockOrientation::South, orientation);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i, j, k, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i, j, k, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i, j, k + 1, texOffsets[0] + 1, texOffsets[1]);
		}

		if (i == WORLD_CHUNK_WIDTH - 1 || m_Blocks[i + 1][k][j] == MinecraftBlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, MinecraftBlockOrientation::North, orientation);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, texOffsets[0], texOffsets[1] + 1);
		}

		// Bottom
		if (j == 0 || m_Blocks[i][k][j - 1] == MinecraftBlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, MinecraftBlockOrientation::Down, orientation);
			vertices[currentVertex++] = Byte5Data(i, j, k, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i, j, k, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i, j, k + 1, texOffsets[0], texOffsets[1]);
		}

		// Top
		if (j == WORLD_CHUNK_HEIGHT - 1 || m_Blocks[i][k][j + 1] == MinecraftBlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, MinecraftBlockOrientation::Up, orientation);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte5Data(i, j + 1, k, texOffsets[0], texOffsets[1] + 1);
		}

		return currentVertex;
	}
}