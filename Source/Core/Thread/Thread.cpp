#include "Thread.h"

#include <assert.h>

namespace Core
{
	uint32_t RunnableTaskList::Run()
	{
		m_IsRunning = true;

		while (m_IsRunning)
		{
			m_Lock.lock();
			if (!m_Jobs.empty())
			{
				auto job = m_Jobs.front();
				m_Jobs.pop();
				m_Lock.unlock();
				job->Execute();
			}
			else
			{
				m_Lock.unlock();
				std::this_thread::yield();
			}
		}
		return uint32_t();
	}

	void RunnableTaskList::Stop()
	{
		m_IsRunning = false;
	}

	void RunnableTaskList::QueueJob(std::shared_ptr<Job> job)
	{
		m_Lock.lock();
		m_Jobs.push(job);
		m_Lock.unlock();
	}

	RunnableThread::RunnableThread()
		: m_IsInitialized(false)
	{
	}

	RunnableThread::RunnableThread(Runnable * runnable)
		: m_IsInitialized(false)
	{
		runnable->Init();
	}

	void RunnableThread::Init(Runnable * runnable)
	{
		assert(m_IsInitialized == false);
		runnable->Init();
		m_Thread = new std::thread(&Runnable::Run, runnable);
		m_Runnable = runnable;
		m_IsInitialized = true;
	}

	void RunnableThread::Shutdown()
	{
		if (m_IsInitialized)
		{
			m_Runnable->Stop();
			m_Thread->join();
			delete m_Thread;
			m_Thread = nullptr;
			m_IsInitialized = false;
		}
	}

	RunnableThread::~RunnableThread()
	{
		Shutdown();
	}
}

