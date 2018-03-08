#pragma once

#include "Core/Singleton/Singleton.h"

#include <stdint.h>

#define BLOCK_DATABASE_VERSION 1

namespace Game
{
	enum class BlockType : uint8_t
	{
		Air = 0,
		Grass = 1,
		Dirt = 2,
		Stone = 3,
		//Water,
		TypeCount
	};

	enum class BlockOrientation : uint8_t
	{
		North,
		East,
		South,
		West,
		Up,
		Down,
		OrientationCount
	};

	enum class BlockFace : uint8_t
	{
		Front,
		Back,
		Left,
		Right,
		Top,
		Bottom,
		FaceCount
	};

	struct BlockDataBase;

	struct BlockData
	{
		friend BlockDataBase;

	public:

		const uint8_t* GetTextureOffsets(BlockFace face) const { return &(m_TexOffset[static_cast<uint32_t>(face) * 2]); }

	private:
		uint8_t m_TexOffset[static_cast<uint32_t>(BlockFace::FaceCount) * 2];

	};

	struct BlockDataBase : public Core::Singleton<BlockDataBase>
	{
	public:
		SINGLETON_DECLARATION(BlockDataBase);

		void InitTest();
		void LoadBlockDataBase(const char* filename);
		void SaveBlockDataBase(const char* filename);

		const uint8_t* GetTextureOffsets(BlockType type, BlockFace face) const
		{
			return m_BlockData[static_cast<uint32_t>(type)].GetTextureOffsets(face);
		}

	private:
		BlockDataBase() {};
		~BlockDataBase() {};

	private:
		BlockData m_BlockData[static_cast<uint32_t>(BlockType::TypeCount)];
	};
}