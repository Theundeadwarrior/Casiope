#pragma once

#include "Core\Singleton\Singleton.h"

#include <stdint.h>
#include <map>

namespace Core
{
	enum FileOpenFlags
	{
		FileOpen_Read		= 0 << 0,
		FileOpen_Write		= 1 << 0,
		FileOpen_ReadWrite	= 1 << 1,

		FileOpen_Create		= 1 << 4
	};

	class File
	{
	public:
		bool Read(uint32_t maxReadSize, char* buffer);

	private:
		FileOpenFlags m_FileMode;
	};

	class FileSystem : public Core::Singleton<FileSystem>
	{
	public:
		SINGLETON_DECLARATION(FileSystem);

		File* OpenFile(const char* path, FileOpenFlags flags);
		void CloseFile(File* file);


	private:
		FileSystem() {};
		~FileSystem() {};

	private:
		//std::map<File> m_OpenedFiles;
	};
}
