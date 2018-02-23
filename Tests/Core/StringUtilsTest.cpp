#include "catch.hpp"
#include "Core/String/StringUtils.h"

TEST_CASE("Get Extension returns the extension")
{
	const char* filename = "myFileName.bmp";

	const char* ext = Core::GetFileExtension(filename);
	REQUIRE(strcmp(ext, "bmp") == 0);
}