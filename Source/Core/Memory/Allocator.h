#pragma once

#include <stdint.h>

template<uint32_t SIZE>
class StackAllocator
{
public:
	bool Alloc(void* ptr, uint32_t size)
	{
		if (m_AllocatedSize + size < SIZE)
		{
			ptr = static_cast<void*>(m_Buffer[m_AllocatedSize]);
			m_AllocatedSize += size;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Free()
	{
	}

private:
	char m_Buffer[SIZE];
	uint32_t m_AllocatedSize;
};