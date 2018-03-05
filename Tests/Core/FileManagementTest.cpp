#include "catch.hpp"
#include "Core/File/FileSystem.h"

#include <stdlib.h>

TEST_CASE("OpenFileForRead")
{
	auto* fileSystem = Core::FileSystem::CreateInstance();

	Core::File* file = fileSystem->OpenRead("test.txt");

	REQUIRE(file != nullptr);
	REQUIRE(file->GetSize() == 0);
	REQUIRE(file->IsReadMode());

	fileSystem->CloseFile(file);

	Core::FileSystem::DestroyInstance();
}

TEST_CASE("OpenFileForWrite")
{
	auto* fileSystem = Core::FileSystem::CreateInstance();

	Core::File* file = fileSystem->OpenWrite("test2.txt");

	REQUIRE(file != nullptr);
	REQUIRE(file->GetSize() == 0);
	REQUIRE(file->IsWriteMode());

	// Try writting something to the file
	std::string myString = "This is a string";
	file->Write((uint8*)myString.c_str(), myString.length());

	REQUIRE(file != nullptr);
	REQUIRE(file->GetSize() == 16);

	fileSystem->CloseFile(file);

	Core::FileSystem::DestroyInstance();
}

TEST_CASE("OpenFileForReadTwiceShouldWork")
{
	auto* fileSystem = Core::FileSystem::CreateInstance();
	Core::File* file1 = fileSystem->OpenRead("test2.txt");

	REQUIRE(file1 != nullptr);
	REQUIRE(file1->GetSize() == 16); // already written to in last test
	
	Core::File* file2 = fileSystem->OpenRead("test2.txt");

	REQUIRE(file2 != nullptr);
	REQUIRE(file2->GetSize() == 16);

	fileSystem->CloseFile(file2);
	fileSystem->CloseFile(file1);
	Core::FileSystem::DestroyInstance();
}

TEST_CASE("ReadFileAndVerifyBufferTermination")
{
	auto* fileSystem = Core::FileSystem::CreateInstance();
	Core::File* file1 = fileSystem->OpenRead("test2.txt");

	size_t fileSize = file1->GetSize();
	

	void* buffer = malloc(fileSize + 1);
	static_cast<uint8*>(buffer)[fileSize] = '\0';
	file1->Read(static_cast<uint8*>(buffer), file1->GetSize());

	REQUIRE(strlen(static_cast<char*>(buffer)) == 16);
}
