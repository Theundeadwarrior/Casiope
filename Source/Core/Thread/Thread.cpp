#include "Thread.h"

namespace Core
{
	uint32_t RunnableTaskList::Run()
	{
		while (m_IsRunning)
		{
			m_Lock.lock();
			auto job = m_Jobs.front();
			if (job != nullptr)
			{
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

	inline void RunnableTaskList::Stop()
	{
		m_IsRunning = false;
	}

	void RunnableTaskList::QueueJob(std::shared_ptr<Job> job)
	{
		m_Lock.lock();
		m_Jobs.push(job);
	}
}

