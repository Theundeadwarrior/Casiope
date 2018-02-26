#pragma once

#include <stdint.h>

#define BLOCK_DATABASE_VERSION 1

namespace Game
{
	enum class MinecraftBlockType : uint8_t
	{
		Air = 0,
		Grass = 1,
		Dirt = 2,
		Stone = 3,
		//Water,
		TypeCount
	};

	enum class MinecraftBlockOrientation : uint8_t
	{
		North,
		East,
		South,
		West,
		Up,
		Down,
		OrientationCount
	};

	enum class MinecraftBlockFace : uint8_t
	{
		Front,
		Back,
		Left,
		Right,
		Top,
		Bottom,
		FaceCount
	};

	struct MinecraftBlockDataBase;

	struct MinecraftBlockData
	{
		friend MinecraftBlockDataBase;

	public:

		const uint8_t* GetTextureOffsets(MinecraftBlockFace face) const { return &(m_TexOffset[static_cast<uint32_t>(face) * 2]); }

	private:
		uint8_t m_TexOffset[static_cast<uint32_t>(MinecraftBlockFace::FaceCount) * 2];

	};

	struct MinecraftBlockDataBase
	{
	public:
		MinecraftBlockDataBase();

		void InitTest();

		void LoadBlockDataBase(const char* filename);
		void SaveBlockDataBase(const char* filename);

		const uint8_t* GetTextureOffsets(MinecraftBlockType type, MinecraftBlockFace face) const
		{
			return m_BlockData[static_cast<uint32_t>(type)].GetTextureOffsets(face);
		}

	private:
		MinecraftBlockData m_BlockData[static_cast<uint32_t>(MinecraftBlockType::TypeCount)];
	};
}