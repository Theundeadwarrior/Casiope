#pragma once

#include "Renderer/Model/Model.h"
#include "Game/World/MinecraftBlockData.h"

#define WORLD_CHUNK_WIDTH		10
#define WORLD_CHUNK_LENGHT		10
#define WORLD_CHUNK_HEIGHT		10
#define WORLD_BLOCK_COUNT		WORLD_CHUNK_HEIGHT * WORLD_CHUNK_LENGHT * WORLD_CHUNK_WIDTH

namespace Game
{
	struct Byte5Data;


	// CPU Resource
	class MinecraftWorldChunk : public Renderer::Model
	{
		friend class MinecraftWorld;

	public:
		MinecraftWorldChunk(const MinecraftBlockDataBase& database) : m_BlockDataBase(&database) {}
		virtual ~MinecraftWorldChunk() override;

		bool NeedsUpdate() const { return m_NeedsUpdate; }
		void UpdateWorldChunkMesh();

		MinecraftBlockType GetBlock(uint32_t x, uint32_t y, uint32_t z) const;
		void SetBlock(uint32_t x, uint32_t y, uint32_t z, MinecraftBlockType type);
		void SetBlockDataBase(const MinecraftBlockDataBase& database) { m_BlockDataBase = &database; }


	private:
		uint32_t BuildBlockVertices(Byte5Data* vertices, uint32_t x, uint32_t y, uint32_t z);
		const uint8_t* GetTexOffsets(MinecraftBlockType type, MinecraftBlockOrientation face, MinecraftBlockOrientation orientation);

	private:
		MinecraftBlockType m_Blocks[WORLD_CHUNK_WIDTH][WORLD_CHUNK_LENGHT][WORLD_CHUNK_HEIGHT];
		const MinecraftBlockDataBase* m_BlockDataBase;
		glm::ivec3 m_Position = { 0, 0, 0 };
		bool m_NeedsUpdate = false;
	};

}