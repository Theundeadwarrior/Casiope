#include "catch.hpp"
#include "Core/File/FileManagement.h"

TEST_CASE("OpenFileForRead")
{
	Core::FileSystem::CreateInstance();

	Core::File* file = Core::FileSystem::GetInstance()->OpenFile("test.txt", Core::FileOpenFlags::FileOpen_Create);

	Core::FileSystem::DestroyInstance();

}