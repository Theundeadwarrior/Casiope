#pragma once

#include <Core/Core.h>

#include <map>
#include <Core/Memory/Memory.h>

// TODO: Find a way to have a std::map and not a std::map* for the dllexport

struct DLL_EXPORT PointerInfo
{
public:
	int refCount;
};

class DLL_EXPORT DebugAllocator : public MemoryAllocator
{
public:
	void* Malloc(size_t size, uint32_t alignment) override;
	void* Realloc(void* ptr, size_t newSize, uint32_t alignment) override;
	void Free(void* ptr) override;

	DebugAllocator();
	~DebugAllocator();

private:
	std::map<size_t, PointerInfo*>* m_debugInfo;
};

