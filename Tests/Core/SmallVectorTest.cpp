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