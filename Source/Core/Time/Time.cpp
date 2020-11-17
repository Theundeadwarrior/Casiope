#include "Time.h"

namespace Core
{

    Timer::Timer(bool autoStart)
    {
        if (autoStart == true)
        {
            Start();
        }
    }

    void Timer::Start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_IsRunning = true;
    }

    void Timer::Stop()
    {
        m_StopTime = std::chrono::system_clock::now();
        m_IsRunning = false;
    }

    double Timer::GetElapsedMilliSeconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime = GetEndTime();
        return std::chrono::duration<double, std::milli>(endTime - m_StartTime).count();
    }

    double Timer::GetElapsedMicroSeconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime = GetEndTime();
        return std::chrono::duration<double, std::micro>(endTime - m_StartTime).count();
    }

    std::chrono::time_point<std::chrono::system_clock> Timer::GetEndTime()
    {
        if (m_IsRunning)
            return std::chrono::system_clock::now();

        return m_StopTime;
    }
}