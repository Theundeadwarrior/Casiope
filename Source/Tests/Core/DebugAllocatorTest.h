#pragma once

#include "Framework\UnitTestsFramework.h"
#include "Memory\DebugAllocator.h"

TEST_CASE(AllocateSizeZero)
{
	DebugAllocator allocator;
	int* ptr = (int*)allocator.MAlloc(0);
	CHECK(ptr);
	allocator.Free(ptr);
}

TEST_CASE(Allocate2Int)
{
	DebugAllocator allocator;
	int* ptr = (int*)allocator.MAlloc(sizeof(int) * 2);
	CHECK(ptr);
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
	CHECK(ptr1);
	CHECK(ptr2);
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