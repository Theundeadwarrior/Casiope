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

	enum PlanetType
	{
		PlanetType_Normal,
		PlanetType_Arctic,
		PlanetType_Desert,
		PlanetType_Toxic,
		PlanetType_Radioactive,
		PlanetType_Dead,
		PlanetType_Ocean,
		PlanetType_Forest,
		PlanetType_Volcano,
		PlanetType_Cloud
	};

	struct PlanetParameters
	{
		PlanetParameters()
			: m_SkyBoxName("textures/skybox/thickcloudswater/thickclouds.png")
			, m_Type(PlanetType_Normal)
			, m_AverageTemperature(20)
			, m_AverageHumidity(60)
			, m_CircumferenceInChunks(20)
			, m_AllowedHeightInChunks(5)
			, m_WaterLevelInBlocks(64)
			, m_AverageSurfaceLevelInBlocks(150)
		{
		}

		std::string m_SkyBoxName;
		PlanetType m_Type;

		uint32_t m_AverageTemperature;
		uint32_t m_AverageHumidity;

		// The planet has different parameters when generated:
		uint32_t m_CircumferenceInChunks; // How many chunks in width in length before we circle back.
		uint32_t m_AllowedHeightInChunks; // How high can a player go in chunks?
		uint32_t m_WaterLevelInBlocks; // How many blocks high is the water from the bottom of the level.
		uint32_t m_AverageSurfaceLevelInBlocks; // How many blocks high is the surface from the bottom.
	};

	class Planet
	{
	public:
		Planet(const PlanetParameters& parameters);
		~Planet();

		void Initialize(const PlanetParameters& parameters);
		void Update(const glm::vec3& cameraPos);
		std::list<Renderer::Model*>* GetModels() { return m_ChunkManager->GetModels(); }
		std::vector<Renderer::Light>* GetLights() { return &m_Lights; } // todo: whenever we update the chunks, we need to update the list of lights.
		Renderer::Model* GetSkyBox() { return &m_SkyBox; }

	private:
		std::vector<Renderer::Light> m_Lights;
		Renderer::SkyBox m_SkyBox;

		std::shared_ptr<ChunkManager> m_ChunkManager;
	};
}
