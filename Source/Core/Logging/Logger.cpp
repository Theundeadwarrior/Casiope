#include "Logger.h"

#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

#include <iostream>
#include <fstream>

namespace Core
{
	Logger::Logger()
	{}

	Logger::~Logger()
	{}


	void Logger::Initialize()
	{
		std::string filepath = "logging.config";
		try
		{
			std::ifstream configFile(filepath);
			if (configFile.good())
			{
				log4cxx::PropertyConfigurator::configure(filepath);
			}
			else
			{
				log4cxx::BasicConfigurator::configure();
				log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getInfo());
			}

			m_Logger = log4cxx::Logger::getLogger("core.logging");

			LOG4CXX_INFO(m_Logger, "Logger initialized");
		}
		catch (log4cxx::helpers::Exception&)
		{
			std::cerr << "Could not initialize logger ... no logs will be generated" << std::endl;
		}
	}

	void Logger::Shutdown()
	{

	}
}
