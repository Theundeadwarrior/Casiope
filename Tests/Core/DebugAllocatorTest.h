#pragma once

#include "Framework/UnitTestsFramework.h"
#include "Core/Memory/DebugAllocator.h"

TEST_CASE(AllocateSizeZero)
{
	DebugAllocator allocator;
	int* ptr = (int*)allocator.MAlloc(0);
	CHECK(ptr != nullptr);
	allocator.Free(ptr);
}

TEST_CASE(Allocate2Int)
{
	DebugAllocator allocator;
	int* ptr = (int*)allocator.MAlloc(sizeof(int) * 2);
	CHECK(ptr != nullptr);
	*ptr = 32;
	*(ptr + 1) = 54;
	CHECK(*ptr == 32);
	CHECK(*(ptr + 1) == 54);
	allocator.Free(ptr);
}

TEST_CASE(AllocateMultipleTimes)
{
	DebugAllocator allocator;
	int* ptr1 = (int*)allocator.MAlloc(sizeof(int));
	int* ptr2 = (int*)allocator.MAlloc(sizeof(int));
	CHECK(ptr1 != nullptr);
	CHECK(ptr2 != nullptr);
	*ptr1 = 32;
	*ptr2 = 43;
	CHECK(*ptr1 == 32);
	CHECK(*ptr2 == 43);
	allocator.Free(ptr1);
	allocator.Free(ptr2);
}

TEST_CASE(FreeNotAllocMem)
{
	DebugAllocator allocator;
	int* ptr = nullptr;
	allocator.Free(ptr);
}
