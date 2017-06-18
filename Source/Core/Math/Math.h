#pragma once

namespace Core
{
	template<typename T>
	inline static T Min(const T a, const T b)
	{
		return (a < b) ? a : b;
	}
}