#include "bgepch.h"
#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Bge
{
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

	std::string Logger::m_RegFormat;
	std::string Logger::m_StackTraceFormat;

	std::vector<std::string> Logger::m_StackTrace;
	std::map<std::string, std::shared_ptr<spdlog::logger>> Logger::loggers;

	void Logger::Init()
	{
		using namespace std::literals::chrono_literals;

		std::ofstream ofs;
		ofs.open("../logs/core.log", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		std::ofstream ofs2;
		ofs2.open("clientLogs/client.log", std::ofstream::out | std::ofstream::trunc);
		ofs2.close();

		m_StackTrace = {};

		m_RegFormat = "%D %T [%n] [%l]:    %v";
		m_StackTraceFormat = "	at %v";

		s_CoreLogger = spdlog::basic_logger_mt("bge", "../logs/core.log");
		s_ClientLogger = spdlog::basic_logger_mt("client", "clientLogs/client.log");

		s_CoreLogger->set_pattern(m_RegFormat);
		s_ClientLogger->set_pattern(m_RegFormat);

		spdlog::flush_every(1s);
	}

	void Logger::CreateLogger(const std::string& loggerName, const std::string& filepath)
	{ 
		loggers.insert({ loggerName, spdlog::basic_logger_mt(loggerName, filepath) });
		loggers.find(loggerName)->second->set_pattern(m_RegFormat);

		std::ofstream ofs;
		ofs.open(filepath, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}

	void Logger::CreateConsoleLogger(const std::string& loggerName)
	{ 
		loggers.insert({ loggerName, spdlog::stdout_color_mt(loggerName) });
		loggers.find(loggerName)->second->set_pattern("%D %T [%n] [%l]:    %v");
	}

	std::shared_ptr<spdlog::logger> Logger::GetLogger(const std::string& loggerName)
	{ 
		return loggers.find(loggerName)->second;
	}

	void Logger::SetActivePattern(LogFormats format)
	{
		if (format == LogFormats::Regular)
		{
			s_CoreLogger->set_pattern(m_RegFormat);
			s_ClientLogger->set_pattern(m_RegFormat);
		}
		else
		{
			s_CoreLogger->set_pattern(m_StackTraceFormat);
			s_ClientLogger->set_pattern(m_StackTraceFormat);
		}
	}

	void Logger::Trace()
	{
		s_CoreLogger->set_pattern(m_StackTraceFormat);
		for (int i = (size_t)m_StackTrace.size() - 1; i > -1; i = i - 1)
		{	
			s_CoreLogger->info(m_StackTrace[i]);
		}
		s_CoreLogger->set_pattern(m_RegFormat);
	}

	void Logger::ClientTrace()
	{
		s_ClientLogger->set_pattern(m_StackTraceFormat);
		for (int i = (size_t)m_StackTrace.size() - 1; i > -1; i = i - 1)
		{
			s_ClientLogger->info(m_StackTrace[i]);
		}
		s_ClientLogger->set_pattern(m_RegFormat);
	}
}