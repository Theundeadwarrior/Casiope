#pragma once

#include <list>
#include "Core/Math/Vector.h"
#include "Renderer/Mesh/MinecraftWorldMesh.h"

#define WORLD_CHUNK_WIDTH		4
#define WORLD_CHUNK_LENGHT		4
#define WORLD_CHUNK_HEIGHT		4
#define WORLD_BLOCK_COUNT		WORLD_CHUNK_HEIGHT * WORLD_CHUNK_LENGHT * WORLD_CHUNK_WIDTH
// we would only draw vertices if they are 
#define WORLD_MAX_VERTEX_COUNT	WORLD_BLOCK_COUNT * 36 / 2

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

	class MinecraftWorldChunk
	{
	public:
		MinecraftWorldChunk()
			: m_Mesh(WORLD_CHUNK_WIDTH, WORLD_CHUNK_LENGHT, WORLD_CHUNK_HEIGHT)
		{
		}

		void UpdateWorldChunkMesh();
		
		Renderer::MinecraftChunkMesh m_Mesh;
		MinecraftBlockType m_Blocks[WORLD_CHUNK_WIDTH][WORLD_CHUNK_LENGHT][WORLD_CHUNK_HEIGHT];
		Core::Vector3 m_Position = { 0, 0, 0 };
		// todo: cache important information
	};

	class MinecraftWorld
	{
	public:
		MinecraftWorld();
		~MinecraftWorld();

		void InitTestWorld();

	private:
		std::list<MinecraftWorldChunk*> m_LoadedChunks;
	};

}
