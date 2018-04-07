#pragma once

#include "Core/Noise/Noise.h"

#include "Game/Block/BlockData.h"
#include "Game/World/WorldGeneration.h"

#include "Renderer/Model/ChunkMesh.h"
#include "Renderer/SkyBox/SkyBox.h"

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

	struct PlanetParameters
	{
		// The planet has different parameters when generated:
		uint32_t m_CircumferenceInChunks; // How many chunks in width in length before we circle back.
		uint32_t m_AllowedHeightInChunks; // How high can a player go in chunks?
		uint32_t m_WaterLevelInBlocks; // How many blocks high is the water from the bottom of the level.
		uint32_t m_SurfaceLevelInBlocks; // How many blocks high is the surface from the bottom.
	};

	class Planet
	{
	public:
		Planet();
		~Planet();

		void InitTestPlanet();
		void Update();
		std::list<Renderer::Model*>* GetModels() { return &m_LoadedChunks; }
		std::vector<Renderer::Light>* GetLights() { return &m_Lights; } // todo: whenever we update the chunks, we need to update the list of lights.
		Renderer::Model* GetSkyBox() { return &m_SkyBox; }

	private:
		WorldChunk* LoadChunk(int32_t x, int32_t y, int32_t z);
		void SaveChunk(const WorldChunk& chunk);

	private:
		std::list<Renderer::Model*> m_LoadedChunks;
		std::vector<Renderer::Light> m_Lights;
		
		WorldChunk* m_CurrentChunk; // player is currently in that chunk
		Renderer::SkyBox m_SkyBox;

		WorldGenerator m_WorldGenerator;
	};
}
