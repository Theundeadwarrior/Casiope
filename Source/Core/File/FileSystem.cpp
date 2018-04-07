#include "FileSystem.h"

#include "Core/Logging/Logger.h"

#include <string>

#if USING( PLATFORM_WINDOWS )
#include <Windows.h>
#endif // #if USING( PLATFORM_WINDOWS )

namespace Core
{
	File* FileSystem::OpenWrite(const std::string& path, bool isAppending /*= false*/)
	{
#if USING( PLATFORM_WINDOWS )
		uint32 access = GENERIC_WRITE;
		uint32 share = 0;
		uint32 create = isAppending ? OPEN_ALWAYS : CREATE_ALWAYS;
		uint32 flags = FILE_ATTRIBUTE_NORMAL;

		auto handle = CreateFile(path.c_str(), access, share, NULL, create, flags, NULL);
		if (handle == INVALID_FILE_HANDLE)
		{
			// todo lcharbonneau: log somewhere else
			CORE_LOG()->info("Failed to OpenWrite with error: %i", GetLastError());
			return nullptr;
		}
#endif // #if USING( PLATFORM_WINDOWS )

		File* file = new File(FileOpenMode::FileOpen_Write, handle);
		m_OpenedFiles.insert(file);
		return file;
	}

	File* FileSystem::OpenRead(const std::string& path)
	{
#if USING( PLATFORM_WINDOWS )
		uint32 access = GENERIC_READ;
		uint32 share = FILE_SHARE_READ;
		uint32 create = OPEN_EXISTING;
		uint32 flags = FILE_ATTRIBUTE_NORMAL;

		auto handle = CreateFile(path.c_str(), access, share, NULL, create, flags, NULL);
		if (handle == INVALID_FILE_HANDLE)
		{
			// todo lcharbonneau: log somewhere else
			CORE_LOG()->info("Failed to OpenRead with error: %i", GetLastError());
			return nullptr;
		}
#endif // #if USING( PLATFORM_WINDOWS )

		File* file = new File(FileOpenMode::FileOpen_Read, handle);
		m_OpenedFiles.insert(file);
		return file;
	}

	void FileSystem::CloseFile(File* file)
	{
		CloseHandle((HANDLE)file->m_FileHandle);
		m_OpenedFiles.erase(file);
		delete file;
	}
}

