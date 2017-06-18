#pragma once

#include "Core\Core.h"
#include "Core\File\File.h"
#include "Core\Singleton\Singleton.h"

#include <set>


namespace Core
{
	class FileSystem : public Core::Singleton<FileSystem>
	{
	public:
		SINGLETON_DECLARATION(FileSystem);

		File* OpenWrite(const std::string& path, bool isAppending = false);
		File* OpenRead(const std::string& path);
		void CloseFile(File* file);

	private:
		FileSystem() {};
		~FileSystem() {};

	private:
		std::set<File*> m_OpenedFiles;
	};
}
