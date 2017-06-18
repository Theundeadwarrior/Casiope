#pragma once

#include "Core\Core.h"

#if USING( PLATFORM_WINDOWS )
#define INVALID_FILE_HANDLE (void*)(-1)
#endif // #if USING( PLATFORM_WINDOWS )

namespace Core
{
#if USING(PLATFORM_WINDOWS)
	typedef void* FileSystemHandle;
#endif // #if USING(PLATFORM_WINDOWS)

	enum FileOpenMode
	{
		FileOpen_Read = 1 << 0,
		FileOpen_Write = 1 << 1,
	};

	enum SeekMethod
	{
		Seek_Begin,
		Seek_Current,
		Seek_End
	};

	class File
	{
	public:
		bool Read(uint8* buffer, uint64 maxReadSize);
		//std::string ReadAll();
		bool Write(uint8* source, uint64 writeSize);

		bool Seek(uint64 pos);
		uint64 Tell() const;
		uint64 GetSize();

		inline bool IsReadMode() const { return m_FileMode == FileOpenMode::FileOpen_Read; }
		inline bool IsWriteMode() const { return m_FileMode == FileOpenMode::FileOpen_Write; }
		inline bool IsValid() const { return m_FileHandle != INVALID_FILE_HANDLE; }

	private:
		friend class FileSystem;
		File(FileOpenMode flags, FileSystemHandle handle);

		int64 FileSeek(int64 distance, SeekMethod method);

	private:
		FileOpenMode m_FileMode;
		FileSystemHandle m_FileHandle;
	};
}
