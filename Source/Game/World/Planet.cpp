#include "Planet.h"

#include "Game/World/WorldGeneration.h"
#include "Game/Chunk/WorldChunk.h"

#include "Core/File/FileSystem.h"
#include "Core/Math/Vector.h"

#include "Engine/GameEngine.h"

#include "Renderer/Light/Light.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Resource/GraphicsResourceManager.h"

#include <vector>


namespace Game
{
	void Planet::Initialize(const PlanetParameters& parameters)
	{
		m_ChunkManager = std::make_shared<ChunkManager>();
		for (int32_t x = -5; x < 5; ++x)
		{
			for (int32_t y = -5; y < 5; ++y)
			{
				auto job = std::make_shared<LoadChunkJob>(LoadChunkJob(m_ChunkManager, x, y, 0));
				Engine::GameEngine::GetInstance()->GetWorkQueue().QueueJob(job);
			}
		}

		m_SkyBox.Init(parameters.m_SkyBoxName);

		// DEBUGGING!!!
		// TESTING SOME LIGHT!!
		//Renderer::DirectionalLight directionLight(glm::vec3(0, 1, 0), glm::vec4(1, 1, 1, 0), 45);
		for (uint32_t i = 0; i < 16; ++i)
		{
			for (uint32_t j = 0; j < 16; ++j)
			{
				for (uint32_t k = 1; k < 5; ++k)
				{
					if (rand() % 4 == 0)
					{
						int radius = rand() % 3 + 1;
						m_Lights.push_back(Renderer::PointLight(glm::vec3(i + 0.2f, k + 0.2f, j + 0.2f), glm::vec4(rand()%80 / 100.0f + 0.2f, rand() % 80 / 100.0f + 0.2f, rand() % 80 / 100.0f + 0.2f, 0), static_cast<float>(radius), 0.3f));
					}
				}
			}
		}

		//m_Lights.push_back(Renderer::PointLight(glm::vec3(4.5f, 4.2f, 4.3f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 6, 0.4f));

		// END OF DEBUGGING!!
	}

	Planet::Planet(const PlanetParameters& parameters)
	{
		Initialize(parameters);
	}

	Planet::~Planet()
	{

	}

	void Planet::Update(const glm::vec3& cameraPos)
	{
		// we'll transfer the new loaded chunks here:
		m_ChunkManager->Update();

		for(auto* model: *m_ChunkManager->GetModels())
		{
			WorldChunk* chunk = static_cast<WorldChunk*>(model);
			chunk->Update(true);
		}
	}
}
