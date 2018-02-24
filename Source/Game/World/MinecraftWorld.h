#pragma once

#include <list>
#include "Renderer/Model/MinecraftWorldMesh.h"
#include "Renderer/Model/Model.h"

namespace Renderer
{
	class Light;
}

#define WORLD_CHUNK_WIDTH		10
#define WORLD_CHUNK_LENGHT		10
#define WORLD_CHUNK_HEIGHT		10
#define WORLD_BLOCK_COUNT		WORLD_CHUNK_HEIGHT * WORLD_CHUNK_LENGHT * WORLD_CHUNK_WIDTH

namespace Game
{
	enum class MinecraftBlockType : uint8_t
	{
		Grass = 1,
		Dirt,
		Stone,
		Water,

		Air = 0
	};

	// CPU Resource
	class MinecraftWorldChunk : public Renderer::Model
	{
	public:
		MinecraftWorldChunk() = default;
		virtual ~MinecraftWorldChunk() override;
		void UpdateWorldChunkMesh();

		MinecraftBlockType GetBlock(uint32_t x, uint32_t y, uint32_t z);

		void SetBlock(uint32_t x, uint32_t y, uint32_t z, MinecraftBlockType type);

		MinecraftBlockType m_Blocks[WORLD_CHUNK_WIDTH][WORLD_CHUNK_LENGHT][WORLD_CHUNK_HEIGHT];
		glm::ivec3 m_Position = { 0, 0, 0 };
		bool m_NeedsUpdate = false;
	};


	// World is in charge of managing the chunks and streaming them as we go. It is also called to see which chunks needs to be updated.
	class MinecraftWorld
	{
	public:
		MinecraftWorld();
		~MinecraftWorld();

	public:
		void InitTestWorld();
		std::list<Renderer::Model*>* GetModels() { return &m_LoadedChunks; }
		std::vector<Renderer::Light>* GetLights() { return &m_Lights; } // todo: whenever we update the chunks, we need to update the list of lights.

	private:
		MinecraftWorldChunk* LoadChunk(int32_t x, int32_t y, int32_t z);
		void SaveChunk(const MinecraftWorldChunk& chunk);

	private:
		std::list<Renderer::Model*> m_LoadedChunks;
		std::vector<Renderer::Light> m_Lights;
		MinecraftWorldChunk* m_CurrentChunk; // player is currently in that chunk
	};
}
