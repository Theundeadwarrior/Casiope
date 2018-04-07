#include "Game/Chunk/WorldChunk.h"

#include "GraphicsCore/Mesh/Mesh.h"


namespace Game
{
	struct Byte8Data
	{
		Byte8Data() {};
		Byte8Data(int8_t x1, int8_t x2, int8_t x3, int8_t x4, int8_t x5, int8_t x6, int8_t x7, int8_t x8)
			: m_x1(x1)
			, m_x2(x2)
			, m_x3(x3)
			, m_x4(x4)
			, m_x5(x5)
			, m_x6(x6)
			, m_x7(x7)
			, m_x8(x8)
		{}

		int8_t m_x1, m_x2, m_x3, m_x4, m_x5, m_x6, m_x7, m_x8;
	};


	WorldChunk::~WorldChunk()
	{
		delete m_Mesh;
	}

	void WorldChunk::ForceUpdate()
	{
		m_NeedsUpdate = true;
		Update();
	}

	void WorldChunk::Update()
	{
		if (m_NeedsUpdate)
		{
			Byte8Data* vertices = static_cast<Byte8Data*>(malloc(WORLD_CHUNK_HEIGHT * WORLD_CHUNK_WIDTH * WORLD_CHUNK_LENGHT * 6 * 6 / 2));
			uint32_t currentVertex = 0;
			for (uint32_t i = 0; i < WORLD_CHUNK_WIDTH; ++i)
			{
				for (uint32_t j = 0; j < WORLD_CHUNK_HEIGHT; ++j)
				{
					for (uint32_t k = 0; k < WORLD_CHUNK_LENGHT; ++k)
					{
						if (m_Blocks[i][k][j] != BlockType::Air)
						{
							currentVertex += BuildBlockVertices(&vertices[currentVertex], i, j, k);
						}
					}
				}
			}
			m_Mesh->UpdateGeometry(vertices, currentVertex * 8, GraphicsCore::VertexBufferType::V3BN3BT2B);
			free(vertices);
			m_NeedsUpdate = false;
		}
	}

	BlockType WorldChunk::GetBlock(uint32_t x, uint32_t y, uint32_t z) const
	{
		return m_Blocks[x][y][z];
	}

	void WorldChunk::SetBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type)
	{
		if (GetBlock(x, y, z) != type)
		{
			m_Blocks[x][y][z] = type;
			m_NeedsUpdate = true;
		}
	}

	const uint8_t* WorldChunk::GetTexOffsets(BlockType type, BlockOrientation face, BlockOrientation orientation)
	{
		BlockFace realFace;
		if (face == BlockOrientation::North)
			realFace = BlockFace::Front;
		else if (face == BlockOrientation::South)
			realFace = BlockFace::Back;
		else if (face == BlockOrientation::East)
			realFace = BlockFace::Left;
		else if (face == BlockOrientation::West)
			realFace = BlockFace::Right;
		else if (face == BlockOrientation::Up)
			realFace = BlockFace::Top;
		else if (face == BlockOrientation::Down)
			realFace = BlockFace::Bottom;
		
		return BlockDataBase::GetInstance()->GetTextureOffsets(type, realFace);
	}

	uint32_t WorldChunk::BuildBlockVertices(Byte8Data* vertices, uint32_t i, uint32_t j, uint32_t k)
	{
		uint32_t currentVertex = 0;
		BlockType type = m_Blocks[i][k][j];

		// Need some data to tell us what direction the block is facing...
		const BlockOrientation orientation = BlockOrientation::North;
		
		if (k == 0 || m_Blocks[i][k - 1][j] == BlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, BlockOrientation::West, orientation);
			vertices[currentVertex++] = Byte8Data(i, j, k, 0, 0, -1, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k, 0, 0, -1, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k, 0, 0, -1, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k, 0, 0, -1, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k, 0, 0, -1, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i, j, k, 0, 0, -1, texOffsets[0] + 1, texOffsets[1]);
		}

		if (k == WORLD_CHUNK_LENGHT - 1 || m_Blocks[i][k + 1][j] == BlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, BlockOrientation::East, orientation);
			vertices[currentVertex++] = Byte8Data(i, j, k + 1, 0, 0, 1, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k + 1, 0, 0, 1, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k + 1, 0, 0, 1, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i, j, k + 1, 0, 0, 1, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k + 1, 0, 0, 1, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k + 1, 0, 0, 1, texOffsets[0], texOffsets[1] + 1);
		}

		if (i == 0 || m_Blocks[i - 1][k][j] == BlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, BlockOrientation::South, orientation);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k + 1, -1, 0, 0, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k, -1, 0, 0, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i, j, k, -1, 0, 0, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k + 1, -1, 0, 0, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i, j, k, -1, 0, 0, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i, j, k + 1, -1, 0, 0, texOffsets[0] + 1, texOffsets[1]);
		}

		if (i == WORLD_CHUNK_WIDTH - 1 || m_Blocks[i + 1][k][j] == BlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, BlockOrientation::North, orientation);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k + 1, 1, 0, 0, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k, 1, 0, 0, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k, 1, 0, 0, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k + 1, 1, 0, 0, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k, 1, 0, 0, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k + 1, 1, 0, 0, texOffsets[0], texOffsets[1] + 1);
		}

		// Bottom
		if (j == 0 || m_Blocks[i][k][j - 1] == BlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, BlockOrientation::Down, orientation);
			vertices[currentVertex++] = Byte8Data(i, j, k, 0, -1, 0, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k, 0, -1, 0, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k + 1, 0, -1, 0, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i, j, k, 0, -1, 0, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j, k + 1, 0, -1, 0, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i, j, k + 1, 0, -1, 0, texOffsets[0], texOffsets[1]);
		}

		// Top
		if (j == WORLD_CHUNK_HEIGHT - 1 || m_Blocks[i][k][j + 1] == BlockType::Air)
		{
			const uint8_t* texOffsets = GetTexOffsets(type, BlockOrientation::Up, orientation);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k, 0, 1, 0, texOffsets[0], texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k + 1, 0, 1, 0, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k, 0, 1, 0, texOffsets[0] + 1, texOffsets[1] + 1);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k + 1, 0, 1, 0, texOffsets[0], texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i + 1, j + 1, k + 1, 0, 1, 0, texOffsets[0] + 1, texOffsets[1]);
			vertices[currentVertex++] = Byte8Data(i, j + 1, k, 0, 1, 0, texOffsets[0], texOffsets[1] + 1);
		}

		return currentVertex;
	}
}