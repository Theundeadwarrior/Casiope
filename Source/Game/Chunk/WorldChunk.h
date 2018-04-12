#pragma once

#include "Renderer/Model/Model.h"
#include "Game/Block/BlockData.h"

#define WORLD_CHUNK_WIDTH		16
#define WORLD_CHUNK_LENGHT		16
#define WORLD_CHUNK_HEIGHT		64
#define WORLD_BLOCK_COUNT		WORLD_CHUNK_HEIGHT * WORLD_CHUNK_LENGHT * WORLD_CHUNK_WIDTH
#define CHUNK_VERSION 1

namespace Game
{
	struct Byte8Data;

	// CPU Resource
	class WorldChunk : public Renderer::Model
	{
		friend class ChunkManager;

	public:
		// todo: fix the constructor to be more user friendly.
		WorldChunk() : m_Vertices(nullptr) {}
		virtual ~WorldChunk() override;

		bool NeedsUpdate() const { return m_NeedsUpdate; }
		void ForceUpdate();
		void Update(bool commitToGPU);

		BlockType GetBlock(uint32_t x, uint32_t y, uint32_t z) const;
		void SetBlock(uint32_t x, uint32_t y, uint32_t z, BlockType type);
		void SetBlockDataBase(const BlockDataBase& database) { }

		glm::ivec3 GetPosition() const
		{
			return m_Position;
		}

		void SetPosition(uint32_t x, uint32_t y, uint32_t z)
		{
			m_Position = glm::ivec3(x, y, z);
			m_Transform.SetTranslate(glm::vec3(m_Position.x * WORLD_CHUNK_WIDTH, m_Position.y * WORLD_CHUNK_HEIGHT, m_Position.z * WORLD_CHUNK_LENGHT));
		}

	private:
		uint32_t BuildBlockVertices(Byte8Data* vertices, uint32_t x, uint32_t y, uint32_t z);
		const uint8_t* GetTexOffsets(BlockType type, BlockOrientation face, BlockOrientation orientation);

	private:
		BlockType m_Blocks[WORLD_CHUNK_WIDTH][WORLD_CHUNK_LENGHT][WORLD_CHUNK_HEIGHT];
		glm::ivec3 m_Position = { 0, 0, 0 };
		Byte8Data* m_Vertices;
		uint32_t m_VertexCount;
		bool m_NeedsUpdate = false;
		bool m_NeedsGPUCommit = false;
		bool m_NeedsSave = false;
	};

}