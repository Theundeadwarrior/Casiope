#pragma once
#include <exception>
#include <list>
#include <functional>

#define CONCATENATE_IMPL(a,b) a##b
#define CONCATENATE(a,b) CONCATENATE_IMPL(a,b)
#define ANONYMOUS_VARIABLE(str) \
	CONCATENATE(str, __COUNTER__)


struct TestRegistry
{
	void RegisterTest(std::function<void()>& fn)
	{
		m_TestsToRun.push_back(fn);
	}

	void RunAllTests()
	{
		for each (auto& test in m_TestsToRun)
		{
			test();
		}
		printf("Tests ran successfully. %lu passed.", (unsigned long)m_TestsToRun.size());
	}

private:
	std::list<std::function<void()>> m_TestsToRun;
};

static TestRegistry s_TestRegistry;

struct AutoRegister
{
	AutoRegister(void(*fn)(), const char* className)
	{
		s_TestRegistry.RegisterTest(std::function<void()>(fn));
	}
};

#define TEST_CASE(name) \
	static void name(); \
	namespace{ AutoRegister ANONYMOUS_VARIABLE(autoRegister) (name, "ANONYMOUS_VARIABLE(name)"); } \
	static void name()

#define TEST_SUITE(name) \
	namespace name

#define CHECK(expr) \
	if (expr == false) throw;