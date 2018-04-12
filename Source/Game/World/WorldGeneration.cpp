#include "Core/Math/Math.h"
#include "Core/Noise/Noise.h"
#include "Core/File/FileSystem.h"

#include "Game/World/WorldGeneration.h"

#include "Renderer/Model/ChunkMesh.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Resource/GraphicsResourceManager.h"
#include "Game/Chunk/WorldChunk.h"


#include <ctime>


namespace Game
{
	LoadChunkJob::LoadChunkJob(std::shared_ptr<ChunkManager> chunkManager, uint32_t x, uint32_t y, uint32_t z)
		: m_ChunkManager(chunkManager)
		, m_X(x)
		, m_Y(y)
		, m_Z(z)
	{
	}

	uint32_t LoadChunkJob::Execute()
	{
		WorldChunk* chunk = m_ChunkManager->LoadChunk(m_X, m_Y, m_Z);

		if (chunk == nullptr)
		{
			chunk = m_ChunkManager->GenerateChunk2(m_X, m_Y, m_Z);
			assert(chunk != nullptr);
		}

		chunk->m_Material = m_ChunkManager->GetMaterial();
		chunk->ForceUpdate();
		m_ChunkManager->AddChunkToWorld(chunk);
		return 0;
	}


	UnloadChunkJob::UnloadChunkJob(std::shared_ptr<ChunkManager> chunkManager, WorldChunk * chunk)
		: m_ChunkManager(chunkManager)
		, m_Chunk(chunk)
	{
	}

	uint32_t UnloadChunkJob::Execute()
	{
		m_ChunkManager->SaveChunk(*m_Chunk);
		delete m_Chunk->m_Mesh;
		delete m_Chunk;
		return 0;
	}

	ChunkManager::ChunkManager()
	{
		m_HeightGenerator.SetFrequency(0.43f);
		m_HeightGenerator.SetFractalLacunarity(1.0);
		
		std::srand(std::time(nullptr)); // use current time as seed for random generator
		m_HeightGenerator.SetSeed(rand()); // todo: remove this and have a seed 

		m_WorldMaterial = new Renderer::TextureMaterial();
		m_WorldMaterial->m_Texture = Renderer::GraphicsResourceManager::GetInstance()->GetTextureManager().CreateTextureFromFile("textures/blocks.png", GraphicsCore::e_TexFormatRGBA);
		m_WorldMaterial->m_ShaderProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateVertexFragmentShaderProgram("shaders/light_accum.vert.glsl", "shaders/light_accum.frag.glsl");
	}

	ChunkManager::~ChunkManager()
	{
		for (auto* chunk : m_LoadedChunks)
		{
			SaveChunk(*(WorldChunk*)chunk);
			delete chunk->m_Mesh;
			delete chunk;
		}

		delete m_WorldMaterial;
	}

	void ChunkManager::Update()
	{
		if (!m_LoadingChunks.empty())
		{
			std::lock_guard<std::mutex> lock(m_LoadingChunksLock);
			for (auto* chunk : m_LoadingChunks)
			{
				chunk->ForceUpdate();
				m_LoadedChunks.push_back(chunk);
			}
			m_LoadingChunks.clear();
		}
	}

	WorldChunk* ChunkManager::CreateFlatChunk(uint32_t x, uint32_t y, uint32_t z)
	{
		WorldChunk* chunk = new WorldChunk();
		chunk->m_Mesh = new Renderer::ChunkMesh();

		for (uint32_t x = 0; x < WORLD_CHUNK_WIDTH; ++x)
		{
			for (uint32_t y = 0; y < WORLD_CHUNK_LENGHT; ++y)
			{
				chunk->SetBlock(x, y, 0, BlockType::Stone);
			}
		}

		chunk->SetPosition(x, y, z);

		return chunk;
	}

	WorldChunk* ChunkManager::LoadChunk(int32_t x, int32_t y, int32_t z)
	{
		char filename[256];
		sprintf_s(filename, "chunks/%08x_%08x_%08x.chunk", x, y, z);

		auto* fs = Core::FileSystem::GetInstance();
		auto* file = fs->OpenRead(filename);

		// Couldn't find the file so we'll generate a new chunk.
		if (file == nullptr)
		{
			return nullptr;
		}

		WorldChunk* loadedChunk = new WorldChunk();
		loadedChunk->m_Mesh = new Renderer::ChunkMesh();

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

	void ChunkManager::SaveChunk(const WorldChunk& chunk)
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

	void ChunkManager::AddChunkToWorld(WorldChunk * chunk)
	{
		std::lock_guard<std::mutex> lock(m_LoadingChunksLock);
		m_LoadingChunks.push_back(chunk);
	}

	Renderer::IMaterial * ChunkManager::GetMaterial() 
	{ 
		return static_cast<Renderer::IMaterial*>(m_WorldMaterial); 
	}


	WorldChunk* ChunkManager::GenerateChunk2(int32_t x, int32_t y, int32_t z)
	{
		WorldChunk* chunk = new WorldChunk();
		chunk->m_Mesh = new Renderer::ChunkMesh();

		for (uint32_t sx = 0; sx < WORLD_CHUNK_WIDTH; ++sx)
		{
			for (uint32_t sy = 0; sy < WORLD_CHUNK_LENGHT; ++sy)
			{
				// remap the value between 0 -> 1
				double value = (m_HeightGenerator.GetSimplexFractal(x + sx / (float)WORLD_CHUNK_WIDTH, y + sy / (float)WORLD_CHUNK_LENGHT) + 1.0) / 2.0;
				
				uint32_t valueint = static_cast<uint32_t>(floor(value * WORLD_CHUNK_HEIGHT));

				uint32_t sz = 0;
				for(sz = 0; sz <= valueint; ++sz)
					chunk->SetBlock(sx, sy, sz, BlockType::Stone);
				if (sz != 0)
				{
					chunk->SetBlock(sx, sy, sz - 1, BlockType::Grass);
				}
				chunk->SetBlock(sx, sy, sz, BlockType::Grass);
			}
		}

		chunk->SetPosition(x, z, y);

		return chunk;
	}
}
