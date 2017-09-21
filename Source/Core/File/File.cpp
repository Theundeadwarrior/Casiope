#include "File.h"

#include <assert.h>
#include <string>

#if USING( PLATFORM_WINDOWS )
#include <Windows.h>
#endif // #if USING( PLATFORM_WINDOWS )



namespace Core
{
	bool File::Read(uint8* buffer, uint64 maxReadSize)
	{
		assert(IsValid() && IsReadMode());

		uint32 bytesRead = 0;
		bool succeed = ReadFile(m_FileHandle, buffer, maxReadSize - 1, &bytesRead, nullptr);

		if (succeed && bytesRead > 0)
		{
			buffer[bytesRead] = '\0';
		}

		return succeed;
	}

	//std::string File::ReadAll()
	//{
	//	return "";
	//}

	bool File::Write(uint8* source, uint64 size)
	{
		assert(IsValid() && IsWriteMode());
		uint32 bytesWritten = 0;
		bool succeed = WriteFile(m_FileHandle, source, size, &bytesWritten, NULL);

		if (!succeed || bytesWritten != size)
			return false;

		return true;
	}

	bool File::Seek(uint64 pos)
	{
		return FileSeek(pos, Seek_Begin) != -1;
	}

	uint64 File::Tell() const
	{
		return uint64();
	}

	uint64 File::GetSize()
	{
		int64 currentPos = FileSeek(0, Seek_Current);
		int64 endPos = FileSeek(0, Seek_End);
		FileSeek(currentPos, Seek_Begin);
		if (currentPos != -1)
			return static_cast<uint64>(endPos);
		else
			return 0;
	}

	File::File(FileOpenMode flags, FileSystemHandle handle)
		: m_FileMode(flags)
		, m_FileHandle(handle)
	{
	}

	int64 File::FileSeek(int64 distance, SeekMethod method)
	{
		LARGE_INTEGER li;
		li.QuadPart = distance;
		li.LowPart = SetFilePointer(m_FileHandle, li.LowPart, &li.HighPart, method);
		if (li.LowPart == -1 && GetLastError() != NO_ERROR)
		{
			li.QuadPart = -1;
		}
		return li.QuadPart;
	}
}