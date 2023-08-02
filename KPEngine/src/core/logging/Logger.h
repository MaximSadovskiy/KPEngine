#pragma once

#include "spdlog/logger.h"
#include <memory>
#include <utility>

template<typename... Args>
using format_string_t = fmt::format_string<Args...>;

//Simple api for logging. For full controll include vendor logger.
#define KPE_GET_LOGGER Kpe::Logger::Get
#define KPE_LOG_SET_LEVEL KPE_GET_LOGGER()->SetLoggerLevel

#define VEND_LOG_LEVEL spdlog::level::level_enum
#define VEND_LOGGER spdlog::logger

#ifdef __KPE_DEBUG__
	#define KPE_INITIAL_LOG_LEVEL Kpe::LEVEL_TRACE
	#define KPE_CONFIGURATION_STR "Debug"
	#define KPE_LOG_DEVICE m_consoleLogger

	#define KPE_LOG_TRACE(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_TRACE, __VA_ARGS__)
	#define KPE_LOG_DEGUB(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_DEBUG, __VA_ARGS__)
	#define KPE_LOG_INFO(...)  KPE_GET_LOGGER()->Log(Kpe::LEVEL_INFO, __VA_ARGS__)
	#define KPE_LOG_WARN(...)  KPE_GET_LOGGER()->Log(Kpe::LEVEL_WARN, __VA_ARGS__)
	#define KPE_LOG_ERROR(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_ERROR, __VA_ARGS__)
	#define KPE_LOG_FATAL(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_FATAL, __VA_ARGS__)

	#define KPE_ASSERT_DEBUG(var, ...) if(var) __VA_ARGS__
	#define KPE_ASSERT_DIST(var, ...)  if(var) __VA_ARGS__
#endif
#ifdef __KPE_RELEASE__
	#define KPE_INITIAL_LOG_LEVEL Kpe::LEVEL_DEBUG
	#define KPE_CONFIGURATION_STR "Release"
	#define KPE_LOG_DEVICE m_consoleLogger

	#define KPE_LOG_TRACE(...) 
	#define KPE_LOG_DEGUB(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_DEBUG, __VA_ARGS__)
	#define KPE_LOG_INFO(...)  KPE_GET_LOGGER()->Log(Kpe::LEVEL_INFO, __VA_ARGS__)
	#define KPE_LOG_WARN(...)  KPE_GET_LOGGER()->Log(Kpe::LEVEL_WARN, __VA_ARGS__)
	#define KPE_LOG_ERROR(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_ERROR, __VA_ARGS__)
	#define KPE_LOG_FATAL(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_FATAL, __VA_ARGS__)

	#define KPE_ASSERT_DEBUG(var, ...) if(var) __VA_ARGS__
	#define KPE_ASSERT_DIST(var, ...)  if(var) __VA_ARGS__
#endif
#ifdef __KPE_DIST__
	#define KPE_INITIAL_LOG_LEVEL Kpe::LEVEL_ERROR
	#define KPE_CONFIGURATION_STR "Distribution"
	#define KPE_LOG_DEVICE m_fileLogger

	#define KPE_LOG_TRACE(...) 
	#define KPE_LOG_DEGUB(...) 
	#define KPE_LOG_INFO(...)  
	#define KPE_LOG_WARN(...)  
	#define KPE_LOG_ERROR(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_ERROR, __VA_ARGS__)
	#define KPE_LOG_FATAL(...) KPE_GET_LOGGER()->Log(Kpe::LEVEL_FATAL, __VA_ARGS__)

	#define KPE_ASSERT_DEBUG(var, ...)
	#define KPE_ASSERT_DIST(var, ...)  if(var) __VA_ARGS__
#endif

namespace Kpe {
	enum LoggerLevel
	{
		LEVEL_TRACE = 0,
		LEVEL_DEBUG = 1,
		LEVEL_INFO = 2,
		LEVEL_WARN = 3,
		LEVEL_ERROR = 4,
		LEVEL_FATAL = 5,
		LEVEL_OFF = 6
	};

	VEND_LOG_LEVEL MatchLevel(Kpe::LoggerLevel level);
	class Logger
	{
	public:
		Logger();
		~Logger();
		static Logger* Get();
		inline void SetLoggerLevel(const Kpe::LoggerLevel& level) const;
		inline void SetConsoleLoggerLevel(const Kpe::LoggerLevel& level) const;
		inline void SetFileLoggerLevel(const Kpe::LoggerLevel& level) const;

		template<typename... Args>
		void Log(const Kpe::LoggerLevel& level, format_string_t<Args...> fmt, Args &&...args) const
		{
			KPE_LOG_DEVICE->log(Kpe::MatchLevel(level), fmt, std::forward<Args>(args)...);
		}
		template<typename... Args>
		void Log(const Kpe::LoggerLevel& level, Args &&...args) const
		{
			KPE_LOG_DEVICE->log(Kpe::MatchLevel(level), std::forward<Args>(args)...);
		}
		template<typename... Args>
		void LogToFile(const Kpe::LoggerLevel& level, Args &&...args) const
		{
			m_fileLogger->log(Kpe::Log::MatchLevel(level), std::forward<Args>(args)...)
		}
		template<typename... Args>
		void LogToConsole(const Kpe::LoggerLevel& level, Args &&...args) const
		{
			m_consoleLogger->log(Kpe::Log::MatchLevel(level), std::forward<Args>(args)...)
		}
	private:
		bool Init();
		std::shared_ptr<VEND_LOGGER>& GetFileLogger();
		std::shared_ptr<VEND_LOGGER>& GetConsoleLogger();

		VEND_LOG_LEVEL m_logLevel;
		std::shared_ptr<VEND_LOGGER> m_fileLogger;
		std::shared_ptr<VEND_LOGGER> m_consoleLogger;
		static Logger* m_logInstance;
	};
}