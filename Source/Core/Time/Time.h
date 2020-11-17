#pragma once

#include <stdint.h>
#include <chrono>

namespace Core
{
    class Timer
    {
    public:
        Timer(bool autoStart = false);

        void Start();
        void Stop();

        double GetElapsedMilliSeconds();
        double GetElapsedMicroSeconds();

    private:
        std::chrono::time_point<std::chrono::system_clock> GetEndTime();

        std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        std::chrono::time_point<std::chrono::system_clock> m_StopTime;
        bool m_IsRunning = false;
    };

}