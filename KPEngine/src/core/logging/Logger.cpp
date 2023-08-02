#include "KpePch.h"	
#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Kpe {
	inline Logger* Kpe::Logger::m_logInstance = Kpe::Logger::Get();

	VEND_LOG_LEVEL Kpe::MatchLevel(LoggerLevel level)
	{
		switch (level)
		{
		case LEVEL_TRACE:
			return VEND_LOG_LEVEL::trace;
		case LEVEL_DEBUG:
			return VEND_LOG_LEVEL::debug;
		case LEVEL_INFO:
			return VEND_LOG_LEVEL::info;
		case LEVEL_WARN:
			return VEND_LOG_LEVEL::warn;
		case LEVEL_ERROR:
			return VEND_LOG_LEVEL::err;
		case LEVEL_FATAL:
			return VEND_LOG_LEVEL::critical;
		case LEVEL_OFF:
			return VEND_LOG_LEVEL::off;
		default:
			return VEND_LOG_LEVEL::n_levels;
		};

	}
	Logger::Logger()
	{
		Init();
	}
	bool Logger::Init()
	{
		m_consoleLogger = spdlog::stdout_color_mt("console_log");
		m_fileLogger = spdlog::basic_logger_mt("file_log", "logs/errors-log.txt");

		m_consoleLogger->set_level(Kpe::MatchLevel(KPE_INITIAL_LOG_LEVEL));
		m_fileLogger->set_level(Kpe::MatchLevel(KPE_INITIAL_LOG_LEVEL));
		m_fileLogger->flush_on(Kpe::MatchLevel(KPE_INITIAL_LOG_LEVEL));

		KPE_LOG_DEVICE->debug("Logger has started!");
		KPE_LOG_DEVICE->debug("Application started, Engine: {0} version.", KPE_CONFIGURATION_STR);
		return true;
	}
	inline void Logger::SetLoggerLevel(const Kpe::LoggerLevel& level) const
	{
		m_consoleLogger->set_level(Kpe::MatchLevel(level));
		m_fileLogger->set_level(Kpe::MatchLevel(level));
	}
	inline void Logger::SetConsoleLoggerLevel(const Kpe::LoggerLevel& level) const
	{
		m_consoleLogger->set_level(Kpe::MatchLevel(level));
	}
	inline void Logger::SetFileLoggerLevel(const Kpe::LoggerLevel& level) const
	{
		m_fileLogger->set_level(Kpe::MatchLevel(level));
	}
	inline std::shared_ptr<VEND_LOGGER>& Logger::GetFileLogger()
	{
		return m_fileLogger;
	}
	inline std::shared_ptr<VEND_LOGGER>& Logger::GetConsoleLogger()
	{
		return m_consoleLogger;
	}
	Kpe::Logger* Logger::Get()
	{
		if (!m_logInstance) m_logInstance = new Logger();
		return m_logInstance;
	}
	Logger::~Logger()
	{
	}
}