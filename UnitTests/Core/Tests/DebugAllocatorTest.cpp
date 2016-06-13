#include "UnitTest++.h"

#include "Memory\DebugAllocator.h"

SUITE(DebugAllocatorTest)
{
	TEST(AllocateSizeZero)
	{
		DebugAllocator allocator;
		int* ptr = (int*)allocator.MAlloc(0);
		CHECK(ptr);
		allocator.Free(ptr);
	}

	TEST(Allocate2Int)
	{
		DebugAllocator allocator;
		int* ptr = (int*)allocator.MAlloc(sizeof(int) * 2);
		CHECK(ptr);
		*ptr = 32;
		*(ptr + 1) = 54;
		CHECK_EQUAL(*ptr, 32);
		CHECK_EQUAL(*(ptr + 1), 54);
		allocator.Free(ptr);
	}
	
	TEST(AllocateMultipleTimes)
	{
		DebugAllocator allocator;
		int* ptr1 = (int*)allocator.MAlloc(sizeof(int));
		int* ptr2 = (int*)allocator.MAlloc(sizeof(int));
		CHECK(ptr1);
		CHECK(ptr2);
		*ptr1 = 32;
		*ptr2 = 43;
		CHECK_EQUAL(*ptr1, 32);
		CHECK_EQUAL(*ptr2, 43);
		allocator.Free(ptr1);
		allocator.Free(ptr2);
	}

	TEST(FreeNotAllocMem)
	{
		DebugAllocator allocator;
		int* ptr = nullptr;
		allocator.Free(ptr);
	}
}