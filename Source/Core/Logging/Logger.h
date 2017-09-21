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

		log4cxx::LoggerPtr GetDefaultLogger() const { return m_Logger; };

	private:
		Logger();
		~Logger();
		 
		log4cxx::LoggerPtr m_Logger;
	};
}