#include <memory>
#include <cstring>
#include <assert.h>

inline uint64_t NextPowerOf2(uint64_t A) {
	A |= (A >> 1);
	A |= (A >> 2);
	A |= (A >> 4);
	A |= (A >> 8);
	A |= (A >> 16);
	A |= (A >> 32);
	return A + 1;
}

template<typename T>
class VectorBase
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;

protected:
	void* m_Begin;
	void* m_End;
	void* m_Capacity;

	VectorBase(void* bufferStart, size_t size)
		: m_Begin(bufferStart)
		, m_End(bufferStart)
		, m_Capacity((char*)bufferStart + size * sizeof(T))
	{
	}

	iterator capacity_ptr() { return (iterator)m_Capacity; }
	const_iterator capacity_ptr() const { return (const_iterator)m_Capacity; }

public:
	// iterators
	iterator begin() { return (iterator)m_Begin; }
	iterator end() { return (iterator)m_End; }
	const_iterator begin() const { return (const_iterator)m_Begin; }
	const_iterator end() const { return (const_iterator)m_End; }

	size_t size() { return end() - begin(); }
	size_t capacity() { return capacity_ptr() - begin(); }
};


// Small buffer allocated on the stack.
template<typename T, unsigned int N>
struct SmallVectorBuffer
{
	char Data[sizeof(T) * N];
};

template<typename T> struct SmallVectorBuffer<T, 0> { char Data[sizeof(T)]; };

template<typename T, unsigned int N>
class SmallVector : public VectorBase<T>
{
	SmallVectorBuffer<T, N> m_SmallBuffer;

	bool IsSmall()
	{
		return m_Begin == (void*)m_SmallBuffer.Data;
	}

	void Grow()
	{
		size_t currentCapacity = (T*)m_Capacity - (T*)m_Begin;
		size_t currentSize = (T*)m_End - (T*)m_Begin;
		size_t newCapacity = NextPowerOf2(currentCapacity + 2);
		
		void* newBuffer = malloc(newCapacity * sizeof(T));
		memcpy(newBuffer, m_Begin, currentCapacity * sizeof(T));

		if (!IsSmall())
		{
			free(m_Begin);
		}

		m_Begin = newBuffer;
		m_End = (void*)((char*)newBuffer + currentSize * sizeof(T));
		m_Capacity = (void*)((char*)newBuffer + newCapacity * sizeof(T));
	}

public:
	SmallVector() : VectorBase((void*)m_SmallBuffer.Data, N) {};

	void push_back(const T& element)
	{
		if (m_End >= m_Capacity)
			Grow();
		memcpy(m_End, &element, sizeof(T));
		m_End = (void*)((char*)m_End + sizeof(T));
	}

	reference operator[](size_t index)
	{
		return *(begin() + index);
	}

	const_reference operator[](size_t index) const
	{
		return *(begin() + index);
	}
};