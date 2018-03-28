#pragma once

#include <spdlog/spdlog.h>

#define CORE_LOG() spdlog::get("core")
#define GRAPHICS_LOG() spdlog::get("graphics")

namespace Core 
{
	namespace Logger
	{
		void Initialize();
		void Shutdown();
	}
}