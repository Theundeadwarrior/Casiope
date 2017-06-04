#include "Core/Core.h"
#include "FileManagement.h"

#if USING( PLATFORM_WINDOWS )
#include <Windows.h>
#endif // #if USING( PLATFORM_WINDOWS )

namespace Core
{
	File* FileSystem::OpenFile(const char * path, FileOpenFlags fileFlags)
	{
		File* file = new File();

#if USING( PLATFORM_WINDOWS )
		uint32_t windowsFlags{};

		if (fileFlags & FileOpenFlags::FileOpen_Read)
			windowsFlags |= OF_READ;
		else if (fileFlags & FileOpenFlags::FileOpen_Write)
			windowsFlags |= OF_WRITE;
		else if (fileFlags & FileOpenFlags::FileOpen_ReadWrite)
			windowsFlags |= OF_READWRITE;

		if (fileFlags & FileOpenFlags::FileOpen_Create)
			windowsFlags |= OF_CREATE;

		OFSTRUCT ofstruct{};

		::OpenFile(path, &ofstruct, windowsFlags);

#endif // #if USING( PLATFORM_WINDOWS )


		//auto test = m_OpenedFiles.insert(file);
		return file;
	}

	void FileSystem::CloseFile(File * file)
	{
	}

	bool File::Read(uint32_t maxReadSize, char * buffer)
	{
		return false;
	}
}

