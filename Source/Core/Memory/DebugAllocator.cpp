#include "DebugAllocator.h"
#include <iostream>

DebugAllocator::DebugAllocator()
{
	m_debugInfo = new std::map<size_t, PointerInfo*>;
}


DebugAllocator::~DebugAllocator()
{
	delete m_debugInfo;
}

void* DebugAllocator::MAlloc(size_t size)
{
	void* ptr = nullptr;
	ptr = malloc(size);
	if (ptr == nullptr)
	{
		std::cout << "malloc returned nullptr. The program will probably crash" << std::endl;
	}

	PointerInfo* ptrInfo = new PointerInfo;
	ptrInfo->refCount = 1;
	(*m_debugInfo)[(size_t)ptr] = ptrInfo;

	return ptr;
}

void DebugAllocator::Free(void* ptr)
{
	PointerInfo* ptrInfo = (*m_debugInfo)[(size_t)ptr];

	if (ptrInfo)
	{
		if (ptrInfo->refCount == 1)
		{
			free(ptr);
			ptrInfo->refCount = 0;
		}
		else
		{
			std::cout << "Memory was already freed." << std::endl;
		}
	}
	else
	{
		std::cout << "Trying to free a pointer not allocated." << std::endl;
	}
}
