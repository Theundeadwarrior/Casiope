#include "catch.hpp"
#include "Core/Memory/DebugAllocator.h"

TEST_CASE("AllocateSizeZero")
{
	DebugAllocator allocator;
	int* ptr = (int*)allocator.MAlloc(0);
	REQUIRE(ptr != nullptr);
	allocator.Free(ptr);
}

TEST_CASE("Allocate2Int")
{
	DebugAllocator allocator;
	int* ptr = (int*)allocator.MAlloc(sizeof(int) * 2);
	REQUIRE(ptr != nullptr);
	*ptr = 32;
	*(ptr + 1) = 54;
	REQUIRE(*ptr == 32);
	REQUIRE(*(ptr + 1) == 54);
	allocator.Free(ptr);
}

TEST_CASE("AllocateMultipleTimes")
{
	DebugAllocator allocator;
	int* ptr1 = (int*)allocator.MAlloc(sizeof(int));
	int* ptr2 = (int*)allocator.MAlloc(sizeof(int));
	REQUIRE(ptr1 != nullptr);
	REQUIRE(ptr2 != nullptr);
	*ptr1 = 32;
	*ptr2 = 43;
	REQUIRE(*ptr1 == 32);
	REQUIRE(*ptr2 == 43);
	allocator.Free(ptr1);
	allocator.Free(ptr2);
}

TEST_CASE("FreeNotAllocMem")
{
	DebugAllocator allocator;
	int* ptr = nullptr;
	allocator.Free(ptr);
}
