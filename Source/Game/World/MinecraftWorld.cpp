#include "MinecraftWorld.h"

#include "Core/File/FileSystem.h"
#include "Core/Math/Vector.h"

#include "Renderer/Light/Light.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Resource/GraphicsResourceManager.h"

#include <vector>

#define CHUNK_VERSION 1

namespace Game
{
	void MinecraftWorld::InitTestWorld()
	{
		auto* testChunk = LoadChunk(0, 0, 0);

		testChunk->m_NeedsUpdate = true;
		testChunk->UpdateWorldChunkMesh();

		m_LoadedChunks.push_back(testChunk);
		m_CurrentChunk = testChunk;

		// Bind the world material to it.
		Renderer::TextureMaterial* worldMaterial = new Renderer::TextureMaterial();
		//worldMaterial->m_Texture = Renderer::GraphicsResourceManager::GetInstance()->GetTextureManager().CreateTextureFromFile("textures/floor/gravel1.bmp", GraphicsCore::e_TexFormatRGB);
		worldMaterial->m_Texture = Renderer::GraphicsResourceManager::GetInstance()->GetTextureManager().CreateTextureFromFile("textures/blocks.png", GraphicsCore::e_TexFormatRGBA);
		worldMaterial->m_ShaderProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateVertexFragmentShaderProgram("shaders/basic_shader.vx", "shaders/basic_shader.fg");
		testChunk->m_Material = worldMaterial;

		// chunk2 for fun
		auto* testChunk2 = LoadChunk(1, 0, 0);
		testChunk2->m_NeedsUpdate = true;
		testChunk2->UpdateWorldChunkMesh();
		m_LoadedChunks.push_back(testChunk2);
		testChunk2->m_Material = worldMaterial;

		// DEBUGGING!!!
		// TESTING SOME LIGHT!!
		Renderer::DirectionalLight directionLight(glm::vec3(0, 1, 0), glm::vec4(1, 1, 1, 0), 45);
		for (uint32_t i = 2; i < 18; ++i)
		{
			for (uint32_t j = 0; j < 10; ++j)
			{
				for (uint32_t k = 2; k < 20; ++k)
				{
					if (rand() % 2 == 0)
					{
						int radius = rand() % 6;
						m_Lights.push_back(Renderer::PointLight(glm::vec3(i, k, j), glm::vec4(1, 0.5f, 0, 0), static_cast<float>(radius), 123.f));
					}
				}
			}
		}
		// END OF DEBUGGING!!
	}

	MinecraftWorldChunk* MinecraftWorld::LoadChunk(int32_t x, int32_t y, int32_t z)
	{
		MinecraftWorldChunk* loadedChunk = new MinecraftWorldChunk();
		loadedChunk->m_Mesh = new Renderer::MinecraftChunkMesh();

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

	// todo: fix this to save a chunk and not the current one all the time...
	void MinecraftWorld::SaveChunk(const MinecraftWorldChunk& chunk)
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

	MinecraftWorld::MinecraftWorld()
	{
		InitTestWorld();
		SaveChunk(*m_CurrentChunk);
	}

	MinecraftWorld::~MinecraftWorld()
	{
		for(auto* chunk : m_LoadedChunks)
		{
			delete chunk;
		}
	}

	void MinecraftWorld::Update()
	{
		for(auto* model: m_LoadedChunks)
		{
			auto* chunk = static_cast<MinecraftWorldChunk*>(model);
			if (chunk->NeedsUpdate())
				chunk->UpdateWorldChunkMesh();
		}
	}
}
