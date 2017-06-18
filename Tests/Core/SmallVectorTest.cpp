#include "catch.hpp"
#include "Core/Containers/SmallVector.h"

TEST_CASE("SmallVector Constructor")
{
	SmallVector<unsigned int, 4> test;
	REQUIRE(test.capacity() == 4);
	REQUIRE(test.size() == 0);
	SmallVector<unsigned int, 0> test2;
	REQUIRE(test2.capacity() == 0);

	struct FakeStruct
	{
		unsigned long int a;
		unsigned long int b;
		unsigned long int c;
		unsigned long int d;
	};

	SmallVector<FakeStruct, 2> test3;
	REQUIRE(test3.capacity() == 2);
	REQUIRE(test3.size() == 0);

	SmallVector<FakeStruct*, 3> test4;
	REQUIRE(test4.capacity() == 3);
	REQUIRE(test4.size() == 0);
}

TEST_CASE("Insert values in SmallVector")
{
	SmallVector<unsigned int, 4> test;
	test.push_back(1);
	REQUIRE(test[0] == 1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(0xFFFFFFFF);
	REQUIRE(test[3] == 0xFFFFFFFF);
}

TEST_CASE("Small vectors work with structs")
{
	struct TestStruct
	{
		uint64_t firstInt;
		uint64_t secondInt;
		uint64_t thirdInt;
		uint64_t fourthInt;
	};

	TestStruct t1;
	t1.fourthInt = 4;
	t1.thirdInt = 3;

	TestStruct t2;
	t2.firstInt = 1;
	t2.secondInt = 2;

	SmallVector<TestStruct, 2> test;
	test.push_back(t1);
	REQUIRE(test[0].fourthInt == 4);
	REQUIRE(test[0].thirdInt == 3);

	test.push_back(t2);
	REQUIRE(test[1].firstInt == 1);
	REQUIRE(test[1].secondInt == 2);
}

TEST_CASE("Small vectors work with uint8")
{
	SmallVector<uint8_t, 4> test;
	test.push_back(65);
	test.push_back(43);
	test.push_back(12);
	test.push_back(9);
	REQUIRE(test[0] == 65);
	REQUIRE(test[1] == 43);
	REQUIRE(test[2] == 12);
	REQUIRE(test[3] == 9);
}