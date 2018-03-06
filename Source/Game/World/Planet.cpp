#include "Planet.h"

#include "Game/World/WorldGeneration.h"
#include "Game/Chunk/WorldChunk.h"

#include "Core/File/FileSystem.h"
#include "Core/Math/Vector.h"

#include "Renderer/Light/Light.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Resource/GraphicsResourceManager.h"

#include <vector>


namespace Game
{
	void Planet::InitTestPlanet()
	{
		Renderer::TextureMaterial* worldMaterial = new Renderer::TextureMaterial();
		worldMaterial->m_Texture = Renderer::GraphicsResourceManager::GetInstance()->GetTextureManager().CreateTextureFromFile("textures/blocks.png", GraphicsCore::e_TexFormatRGBA);
		worldMaterial->m_ShaderProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateVertexFragmentShaderProgram("shaders/basic_shader.vx", "shaders/basic_shader.fg");

		WorldChunk* testChunk = WorldGeneration::CreateFlatChunk(0, 0, 0);//LoadChunk(0, 0, 0);
		testChunk->m_BlockDataBase = &m_BlockDataBase;
		SaveChunk(*testChunk);
		testChunk->ForceUpdate();
		testChunk->m_Material = worldMaterial;

		m_LoadedChunks.push_back(testChunk);
		m_CurrentChunk = testChunk;

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

	WorldChunk* Planet::LoadChunk(int32_t x, int32_t y, int32_t z)
	{
		WorldChunk* loadedChunk = new WorldChunk(&m_BlockDataBase);
		loadedChunk->m_Mesh = new Renderer::ChunkMesh();

		char filename[256];
		sprintf_s(filename, "chunks/%08x_%08x_%08x.chunk", x, y, z);

		auto* fs = Core::FileSystem::GetInstance();
		auto* file = fs->OpenRead(filename);

		// Version: 0xFFFF
		uint16_t version;
		file->Read(reinterpret_cast<uint8_t*>(&version), sizeof(version));
		assert(version == CHUNK_VERSION);

		// MAGIC: 0x7700AABB
		uint32_t magic;
		file->Read(reinterpret_cast<uint8_t*>(&magic), sizeof(magic));
		assert(magic == 0x7700AABB);

		// Coordinates for sanity: 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF
		file->Read(reinterpret_cast<uint8_t*>(&loadedChunk->m_Position), sizeof(loadedChunk->m_Position));
		assert(loadedChunk->m_Position.x == x && loadedChunk->m_Position.y == y && loadedChunk->m_Position.z == z);

		file->Read(reinterpret_cast<uint8_t*>(&loadedChunk->m_Blocks), sizeof(loadedChunk->m_Blocks));

		fs->CloseFile(file);

		loadedChunk->m_Transform.SetTranslate(glm::vec3(loadedChunk->m_Position.x * WORLD_CHUNK_WIDTH, loadedChunk->m_Position.y * WORLD_CHUNK_LENGHT, loadedChunk->m_Position.z * WORLD_CHUNK_HEIGHT));

		return loadedChunk;
	}

	void Planet::SaveChunk(const WorldChunk& chunk)
	{
		char filename[256];
		sprintf_s(filename, "chunks/%08x_%08x_%08x.chunk", chunk.m_Position.x, chunk.m_Position.y, chunk.m_Position.z);

		auto* fs = Core::FileSystem::GetInstance();
		auto* file = fs->OpenWrite(filename);

		uint16_t version = CHUNK_VERSION;
		file->Write(reinterpret_cast<uint8_t*>(&version), sizeof(version));

		uint32_t magic = 0x7700AABB;
		file->Write(reinterpret_cast<uint8_t*>(&magic), sizeof(magic));

		file->Write(reinterpret_cast<const uint8_t*>(&chunk.m_Position), sizeof(chunk.m_Position));

		file->Write(reinterpret_cast<const uint8_t*>(&chunk.m_Blocks), sizeof(chunk.m_Blocks));

		fs->CloseFile(file);
	}

	Planet::Planet()
	{
		m_BlockDataBase.LoadBlockDataBase("blocks.data");

		InitTestPlanet();
	}

	Planet::~Planet()
	{
		for(auto* chunk : m_LoadedChunks)
		{
			delete chunk;
		}
	}

	void Planet::Update()
	{
		for(auto* model: m_LoadedChunks)
		{
			auto* chunk = static_cast<WorldChunk*>(model);
			if (chunk->NeedsUpdate())
				chunk->Update();
		}
	}
}
