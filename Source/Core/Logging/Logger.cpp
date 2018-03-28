#include "Logger.h"

#include <vector>

namespace Core
{
	void Logger::Initialize()
	{
		std::vector<spdlog::sink_ptr> sinks;
		auto winColorSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
		winColorSink->set_level(spdlog::level::trace);
		auto dailyFileSink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("../Logs/log.txt", 0, 0);
		dailyFileSink->set_level(spdlog::level::trace);

		sinks.push_back(winColorSink);
		sinks.push_back(dailyFileSink);
		
		spdlog::register_logger(std::make_shared<spdlog::async_logger>("core", sinks.begin(), sinks.end(), 4096));
		spdlog::register_logger(std::make_shared<spdlog::async_logger>("graphics", sinks.begin(), sinks.end(), 4096));
	}

	void Logger::Shutdown()
	{
		spdlog::drop_all();
	}
}
