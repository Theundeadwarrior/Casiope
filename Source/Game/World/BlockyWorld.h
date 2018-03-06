#pragma once

#include "Game/Block/BlockData.h"

#include "Renderer/Model/ChunkMesh.h"

#include <list>

namespace Renderer
{
	class Light;
	class Model;
}


namespace Game
{
	class WorldChunk;
	// World is in charge of managing the chunks and streaming them as we go. It is also called to see which chunks needs to be updated.
	class BlockyWorld
	{
	public:
		BlockyWorld();
		~BlockyWorld();

		void InitTestWorld();
		void Update();
		std::list<Renderer::Model*>* GetModels() { return &m_LoadedChunks; }
		std::vector<Renderer::Light>* GetLights() { return &m_Lights; } // todo: whenever we update the chunks, we need to update the list of lights.

	private:
		WorldChunk* LoadChunk(int32_t x, int32_t y, int32_t z);
		void SaveChunk(const WorldChunk& chunk);

	private:
		std::list<Renderer::Model*> m_LoadedChunks;
		std::vector<Renderer::Light> m_Lights;
		WorldChunk* m_CurrentChunk; // player is currently in that chunk
		MinecraftBlockDataBase m_BlockDataBase; // todo: move this as a singleton class that the chunk can access...
	};
}
