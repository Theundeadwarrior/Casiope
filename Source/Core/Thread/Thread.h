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

namespace std
{
	class thread;
}

namespace Core
{
	class Runnable;

	class Job
	{
	public:
		virtual ~Job() {}
		virtual uint32_t Execute() = 0;
	};

	class Runnable
	{
	public:
		virtual ~Runnable() {};
		virtual bool Init() { return true; }
		virtual uint32_t Run() = 0;
		virtual void Stop() {}
	};

	class RunnableJob : public Runnable
	{
	public:
		template<typename Func>
		RunnableJob(Func func) : m_Job(func) {}
		virtual uint32_t Run() override
		{
			return m_Job->Execute();
		}
	private:
		std::unique_ptr<Job> m_Job;
	};

	class RunnableTaskList : public Runnable
	{
	public:
		RunnableTaskList() : m_IsRunning(false) {}
		// Inherited via Thread
		virtual uint32_t Run() override;
		virtual void Stop() override;

		void QueueJob(std::shared_ptr<Job> job);

	private:
		std::queue< std::shared_ptr<Job> > m_Jobs;
		std::mutex m_Lock;
		bool m_IsRunning;
	};

	class RunnableThread
	{
	public:
		RunnableThread();
		RunnableThread(Runnable* runnable);
		~RunnableThread();

		void Init(Runnable* runnable);
		void Shutdown();

		Runnable* GetRunnable() { return m_Runnable; }

	private:
		std::thread* m_Thread;
		Runnable* m_Runnable;
		bool m_IsInitialized;
	};
}


