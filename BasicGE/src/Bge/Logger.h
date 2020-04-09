#pragma once

#include "bgepch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/fmt/ostr.h"

namespace Bge
{
	enum class LogFormats
	{
		Regular,
		StackTrace
	};

	class BGE_API Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		static std::string m_RegFormat;
		static std::string m_StackTraceFormat;

		static std::vector<std::string> m_StackTrace;
		static std::map<std::string, std::shared_ptr<spdlog::logger>> loggers;
	public:
		static void Init();
		// static void Clear();

		static void Trace();
		static void ClientTrace();

		template<class ... T> static void Error(T ... args)
		{
			s_CoreLogger->error(args...);
			Trace();
		}
		template<class ... T> static void Warn(T ... args)
		{
			s_CoreLogger->warn(args...);
		}
		template<class ... T> static void Info(T ... args)
		{
			s_CoreLogger->info(args...);
		}

		template<class ... T> static void ClientError(T ... args)
		{
			s_ClientLogger->error(args...);
			ClientTrace();
		}
		template<class ... T> static void ClientWarn(T ... args)
		{
			s_ClientLogger->warn(args...);
		}
		template<class ... T> static void ClientInfo(T ... args)
		{
			s_ClientLogger->info(args...);
		}

		static void CreateLogger(const std::string& loggerName, const std::string& filepath);
		static void CreateConsoleLogger(const std::string& loggerName);
		static std::shared_ptr<spdlog::logger> GetLogger(const std::string& loggerName);

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

		inline static void PopStackFrame() { if (m_StackTrace.size() > 0) m_StackTrace.pop_back(); }
		inline static void PushStackFrame(const std::string& stackFrame) { m_StackTrace.push_back(stackFrame); }

		static void SetActivePattern(LogFormats format);
	};
}

#define BGE_SET_TRACE Bge::Logger::PushStackFrame(__func__ + std::string("[") + __FILE__ + std::string(":") + std::to_string(__LINE__) + std::string("]"))
#define BGE_REMOVE_TRACE Bge::Logger::PopStackFrame()

#define BGE_CORE_INFO(...) Bge::Logger::Info(__VA_ARGS__)
#define BGE_CORE_WARN(...) Bge::Logger::Warn(__VA_ARGS__)
#define BGE_CORE_ERROR(...) { BGE_SET_TRACE; Bge::Logger::Error(__VA_ARGS__); }

#define BGE_INFO(...) Bge::Logger::ClientInfo(__VA_ARGS__)
#define BGE_WARN(...) Bge::Logger::ClientWarn(__VA_ARGS__)
#define BGE_ERROR(...) Bge::Logger::ClientError(__VA_ARGS__)