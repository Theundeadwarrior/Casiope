#pragma once

#include <list>
#include "Core/Math/Vector.h"
#include "Renderer/Model/MinecraftWorldMesh.h"
#include "Renderer/Model/Model.h"

#define WORLD_CHUNK_WIDTH		10
#define WORLD_CHUNK_LENGHT		10
#define WORLD_CHUNK_HEIGHT		10
#define WORLD_BLOCK_COUNT		WORLD_CHUNK_HEIGHT * WORLD_CHUNK_LENGHT * WORLD_CHUNK_WIDTH

namespace Engine
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
	class MinecraftWorldChunk
	{
	public:
		MinecraftWorldChunk() = default;
		void UpdateWorldChunkMesh();

		MinecraftBlockType GetBlock(uint32_t x, uint32_t y, uint32_t z);

		void SetBlock(uint32_t x, uint32_t y, uint32_t z, MinecraftBlockType type);

		Renderer::MinecraftChunkMesh m_Mesh;
		MinecraftBlockType m_Blocks[WORLD_CHUNK_WIDTH][WORLD_CHUNK_LENGHT][WORLD_CHUNK_HEIGHT];
		Core::Vector3 m_Position = { 0, 0, 0 };
		bool m_NeedsUpdate = false;
	};


	// World is in charge of managing the chunks and streaming them as we go. It is also called to see which chunks needs to be updated.
	class MinecraftWorld
	{
	public:
		MinecraftWorld();
		~MinecraftWorld();

		void InitTestWorld();

		Renderer::Model* GetModel() { return &m_Model; }

	private:
		std::list<MinecraftWorldChunk*> m_LoadedChunks;
		MinecraftWorldChunk* m_CurrentChunk; // player is currently in that chunk
		Renderer::Model m_Model;
	};
}
