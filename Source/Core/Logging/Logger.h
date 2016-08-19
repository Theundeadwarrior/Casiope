#pragma once

#include <Core/Singleton/Singleton.h>

#include <log4cxx/logger.h>

namespace core {
	class Logger : public Core::Singleton<Logger>
	{
	public:
		SINGLETON_DECLARATION(Logger);

		void Initialize();
		void Shutdown();

	protected:

	private:
		Logger();
		~Logger();

		log4cxx::LoggerPtr m_Logger;
	};
}