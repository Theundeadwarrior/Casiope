#pragma once

#include "Game/World/MinecraftBlockData.h"

#include "Renderer/Model/MinecraftWorldMesh.h"

#include <list>

namespace Renderer
{
	class Light;
	class Model;
}


namespace Game
{
	class MinecraftWorldChunk;
	// World is in charge of managing the chunks and streaming them as we go. It is also called to see which chunks needs to be updated.
	class MinecraftWorld
	{
	public:
		MinecraftWorld();
		~MinecraftWorld();

		void InitTestWorld();
		void Update();
		std::list<Renderer::Model*>* GetModels() { return &m_LoadedChunks; }
		std::vector<Renderer::Light>* GetLights() { return &m_Lights; } // todo: whenever we update the chunks, we need to update the list of lights.

	private:
		MinecraftWorldChunk* LoadChunk(int32_t x, int32_t y, int32_t z);
		void SaveChunk(const MinecraftWorldChunk& chunk);

	private:
		std::list<Renderer::Model*> m_LoadedChunks;
		std::vector<Renderer::Light> m_Lights;
		MinecraftWorldChunk* m_CurrentChunk; // player is currently in that chunk
		MinecraftBlockDataBase m_BlockDataBase; // todo: move this as a singleton class that the chunk can access...
	};
}
