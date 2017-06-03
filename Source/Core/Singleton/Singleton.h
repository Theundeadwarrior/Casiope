#pragma once
#include <assert.h>

#define SINGLETON_DECLARATION(T) friend Core::Singleton<T>

namespace Core
{
	template<typename T>
	class Singleton
	{
		friend T;
	public:
		static void CreateInstance()
		{
			assert(m_Instance == nullptr);
			m_Instance = new T();
		}
		static void DestroyInstance()
		{
			assert(m_Instance != nullptr);
			delete m_Instance;
			m_Instance = nullptr;
		}

		static T* GetInstance()
		{
			return m_Instance;
		}
	protected:
		Singleton() {}
		virtual ~Singleton() {}
	private:
		Singleton(const Singleton&) = delete;
		static T* m_Instance;
	};

	template<typename T>
	T* Singleton<T>::m_Instance = nullptr;
}

