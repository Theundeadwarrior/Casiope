#pragma once

/*
Here's what we need:
- A Runnable interface that has Init(), Run() Exit() and an implementation of it for a worker thread that has multiple tasks/jobs.
- We need a thread object that is an actual Windows Thread and runs the Runnable. A priority can be set on it to go faster or slower depending on the number of cores...
*/

/*
Unreal has FRunnableThread which are built by passing in a FRunnable which is called when the FRunnableThread Run function is called. The FRunnableThread has a resume/suspend methods
that can be called to pause the running execution.
*/

#include <stdint.h>
#include <queue>
#include <mutex>
#include <functional>

class Job
{
public:
	template<typename Func>
	Job(Func func)
	{
		m_Func = std::bind(func);
	}

	uint32_t Execute()
	{
		return m_Func();
	}

private:
	std::function<uint32_t(void)> m_Func;
};

class Runnable
{
public:
	virtual ~Runnable() {};
	virtual bool Init() { return true; }
	virtual uint32_t Run() = 0;
	virtual void Stop() {}
	virtual void Exit() {}
};

class RunnableTaskList : public Runnable
{
public:
	// Inherited via Thread
	virtual uint32_t Run() override;

	void QueueJob(const Job& job);

private:
	std::queue<Job> m_Jobs;
	std::mutex m_Lock;
};
