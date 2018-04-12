#pragma once

#include "Core/Noise/FastNoise.h"
#include "Core/Thread/Thread.h"

#include <stdint.h>
#include <list>
#include <mutex>

namespace Renderer
{
	class Model;
	class IMaterial;
	class TextureMaterial;
}

namespace Game
{
	class WorldChunk;
	class ChunkManager;

	// ChunkManager will determine which chunks to load/generate according to the planet parameters
	// and the position of the player.

	class LoadChunkJob : public Core::Job
	{
	public:
		LoadChunkJob(std::shared_ptr<ChunkManager> chunkManager, uint32_t x, uint32_t y, uint32_t z);
		virtual uint32_t Execute() override;

	private:
		std::shared_ptr<ChunkManager> m_ChunkManager;
		uint32_t m_X, m_Y, m_Z;
	};

	class UnloadChunkJob : public Core::Job 
	{
	public:
		UnloadChunkJob(std::shared_ptr<ChunkManager> chunkManager, WorldChunk* chunk);
		virtual uint32_t Execute() override;

	private:
		std::shared_ptr<ChunkManager> m_ChunkManager;
		WorldChunk* m_Chunk;
	};

	class ChunkManager
	{
	public:
		ChunkManager();
		~ChunkManager();

		void Update();

		WorldChunk* CreateFlatChunk(uint32_t x, uint32_t y, uint32_t z);
		WorldChunk* GenerateChunk2(int32_t x, int32_t y, int32_t z);

		WorldChunk* LoadChunk(int32_t x, int32_t y, int32_t z);
		void SaveChunk(const WorldChunk& chunk);
		void AddChunkToWorld(WorldChunk* chunk);

		std::list<Renderer::Model*>* GetModels() { return &m_LoadedChunks; }
		Renderer::IMaterial* GetMaterial();

	private:
		Renderer::TextureMaterial* m_WorldMaterial;
		std::list<Renderer::Model*> m_LoadedChunks;
		std::list<WorldChunk*> m_LoadingChunks;
		std::mutex m_LoadingChunksLock;

		Core::FastNoise m_HeightGenerator;
	};
}
