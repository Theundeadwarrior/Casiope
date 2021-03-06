#pragma once

#include <math.h>

namespace Core
{
	template<typename T>
	inline static T Min(const T a, const T b)
	{
		return (a < b) ? a : b;
	}

	template<typename T>
	inline static T Max(const T a, const T b)
	{
		return (a > b) ? a : b;
	}
}