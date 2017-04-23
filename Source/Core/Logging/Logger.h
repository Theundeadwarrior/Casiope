#pragma once

#include <Core/Singleton/Singleton.h>

#include <log4cxx/logger.h>

namespace Core {

	class Logger : public Core::Singleton<Logger>
	{
	public:
		SINGLETON_DECLARATION(Logger);

		void Initialize();
		void Shutdown();


	private:
		Logger();
		~Logger();

		log4cxx::LoggerPtr m_Logger;
	};
}