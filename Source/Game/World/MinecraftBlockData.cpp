#include "Game/World/MinecraftBlockData.h"

#include "Core/File/FileSystem.h"

#include <assert.h>

namespace Game
{
	MinecraftBlockDataBase::MinecraftBlockDataBase()
	{

		//InitTest();
	}

	void MinecraftBlockDataBase::InitTest()
	{
		uint8_t dirtValues[12] = { 1,0,1,0,1,0,1,0,1,0,1,0 };
		memcpy(m_BlockData[static_cast<uint32_t>(MinecraftBlockType::Dirt)].m_TexOffset, dirtValues, 12);

		uint8_t grassValues[12] = { 2,0,2,0,2,0,2,0,3,0,1,0 };
		memcpy(m_BlockData[static_cast<uint32_t>(MinecraftBlockType::Grass)].m_TexOffset, grassValues, 12);

		uint8_t stoneValues[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
		memcpy(m_BlockData[static_cast<uint32_t>(MinecraftBlockType::Stone)].m_TexOffset, stoneValues, 12);

		SaveBlockDataBase("blocks.data");
	}

	void MinecraftBlockDataBase::LoadBlockDataBase(const char* filename)
	{
		auto* fs = Core::FileSystem::GetInstance();
		auto* file = fs->OpenRead(filename);

		// Version: 0xFFFF
		uint16_t version;
		file->Read(reinterpret_cast<uint8_t*>(&version), sizeof(version));
		assert(version == BLOCK_DATABASE_VERSION);

		// MAGIC: 0x7700AABB
		uint32_t magic;
		file->Read(reinterpret_cast<uint8_t*>(&magic), sizeof(magic));
		assert(magic == 0x7700AABB);

		file->Read(reinterpret_cast<uint8_t*>(&m_BlockData), sizeof(m_BlockData));

		fs->CloseFile(file);
	}

	void MinecraftBlockDataBase::SaveBlockDataBase(const char* filename)
	{
		auto* fs = Core::FileSystem::GetInstance();
		auto* file = fs->OpenWrite(filename);

		uint16_t version = BLOCK_DATABASE_VERSION;
		file->Write(reinterpret_cast<uint8_t*>(&version), sizeof(version));

		uint32_t magic = 0x7700AABB;
		file->Write(reinterpret_cast<uint8_t*>(&magic), sizeof(magic));

		file->Write(reinterpret_cast<const uint8_t*>(&m_BlockData), sizeof(m_BlockData));

		fs->CloseFile(file);
	}
}

