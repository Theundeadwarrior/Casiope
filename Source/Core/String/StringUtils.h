#pragma once

#include <cstring>

namespace Core
{
	const char* GetFileExtension(const char* file)
	{
		int len = strlen(file);
		//const char* pos = file + len - 1;
		for (const char* pos = file + len - 1; pos != file; --pos)
		{
			if (*pos == '.')
				return pos + 1;
		}
	}
}