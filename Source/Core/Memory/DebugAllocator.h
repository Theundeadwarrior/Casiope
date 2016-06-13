#pragma once

#include <map>

// TODO: Find a way to have a std::map and not a std::map* for the dllexport

struct __declspec(dllexport) PointerInfo
{
public:
	int refCount;
};

class __declspec(dllexport) DebugAllocator
{
public:
	void* MAlloc(size_t size);
	void Free(void* ptr);

	DebugAllocator();
	~DebugAllocator();

private:
	std::map<size_t, PointerInfo*>* m_debugInfo;
};

