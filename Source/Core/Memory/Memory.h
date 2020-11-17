#include <stdint.h>

// Base class for memory allocator.
class MemoryAllocator
{
public:
    virtual void* Malloc(size_t size, uint32_t alignment) = 0;
    virtual void* Realloc(void* ptr, size_t newSize, uint32_t alignment) = 0;
    virtual void Free(void* ptr) = 0;
};