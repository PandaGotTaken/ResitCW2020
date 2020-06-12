/** \file log.h
*/
#pragma once

#define FMT_DEPRECATED
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace IMAT3905 {

	/**
	\class Log
	A simple logging class which makes use of spdlog.
	This class is intends to be used by the macros below.
	*/

	class Log
	{
	public:
		static void init();
		static void shutdown();
		static std::shared_ptr<spdlog::logger>& getLogger(); //!< Return the logger
	private:
		static std::shared_ptr<spdlog::logger> s_logger; //!< SPD logger
		static bool s_running; //!< Has the logger been started
	};
}


// logging macros
#define LOG_TRACE(...)    IMAT3905::Log::getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     IMAT3905::Log::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     IMAT3905::Log::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    IMAT3905::Log::getLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)    IMAT3905::Log::getLogger()->critical(__VA_ARGS__)



