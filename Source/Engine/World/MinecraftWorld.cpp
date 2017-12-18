#include "MinecraftWorld.h"

#include "Core/File/FileSystem.h"
#include "Core/Math/Vector.h"

#include <vector>

#define CHUNK_VERSION 1

namespace Engine
{
	void MinecraftWorld::InitTestWorld()
	{
		// Faking some data just to make it work.
		MinecraftWorldChunk* testChunk = new MinecraftWorldChunk();

		for (uint32_t i = 0; i < WORLD_CHUNK_WIDTH; ++i)
		{
			for (uint32_t j = 0; j < WORLD_CHUNK_LENGHT; ++j)
			{
					if ((i + j) % 2 == 0)
					{
						testChunk->m_Blocks[i][j][1] = MinecraftBlockType::Grass;
					}
			}
		}
		m_LoadedChunks.push_back(testChunk);
		testChunk->m_NeedsUpdate = true;

		testChunk->UpdateWorldChunkMesh();
		m_CurrentChunk = testChunk;

		// todo revisit this
		m_Model.m_Mesh = &m_CurrentChunk->m_Mesh;
	}

	void MinecraftWorld::LoadChunk(int32_t x, int32_t y, int32_t z)
	{
		char filename[256];
		sprintf_s(filename, "chunks/%08x_%08x_%08x.chunk", x, y, z);

		auto* fs = Core::FileSystem::GetInstance();
		auto* file = fs->OpenRead(filename);

		// MAGIC: 0x7700AABB
		uint32_t magic = 0x7700AABB;
		file->Read(reinterpret_cast<uint8_t*>(&magic), sizeof(magic));
		assert(magic == 0x7700AABB);

		// Version: 0xFFFF


		// Coordinates for sanity: 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF


	}

	// todo: fix this to save a chunk and not the current one all the time...
	void MinecraftWorld::SaveChunk(const MinecraftWorldChunk& chunk)
	{
		char filename[256];
		sprintf_s(filename, "chunks/%08x_%08x_%08x.chunk", chunk.m_Position.x, chunk.m_Position.y, chunk.m_Position.z);

		auto* fs = Core::FileSystem::GetInstance();
		auto* file = fs->OpenWrite(filename);

		uint16_t version = CHUNK_VERSION;
		file->Write(reinterpret_cast<uint8_t*>(&version), sizeof(version));

		uint32_t magic = 0x7700AABB;
		file->Write(reinterpret_cast<uint8_t*>(&magic), sizeof(magic));

		file->Write(reinterpret_cast<const uint8_t*>(&chunk.m_Position), sizeof(chunk.m_Position));

		fs->CloseFile(file);

	}

	MinecraftWorld::MinecraftWorld()
	{
		InitTestWorld();
		//LoadChunk(0, 0, 0);
		SaveChunk(*m_CurrentChunk);
	}

	MinecraftWorld::~MinecraftWorld()
	{
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
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k, 1, 0);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 0);

							vertices[currentVertex++] = Byte5Data(i, j, k + 1, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k + 1, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, 0, 1);

							vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i, j + 1, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i, j, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i, j, k + 1, 0, 0);

							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k, 1, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k + 1, 0, 0);
							vertices[currentVertex++] = Byte5Data(i + 1, j, k, 0, 1);
							vertices[currentVertex++] = Byte5Data(i + 1, j + 1, k + 1, 1, 0);

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
			m_Mesh.Update(vertices, currentVertex * 5);
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
