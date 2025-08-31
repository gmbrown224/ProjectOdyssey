#pragma once

#include "Titus/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Titus
{
	class TITUS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define TE_CORE_TRACE(...)     ::Titus::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TE_CORE_INFO(...)      ::Titus::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TE_CORE_WARN(...)      ::Titus::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TE_CORE_ERROR(...)     ::Titus::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TE_CORE_CRITICAL(...)  ::Titus::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define APP_TRACE(...)     ::Titus::Log::GetClientLogger()->trace(__VA_ARGS__)
#define APP_INFO(...)      ::Titus::Log::GetClientLogger()->info(__VA_ARGS__)
#define APP_WARN(...)      ::Titus::Log::GetClientLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)     ::Titus::Log::GetClientLogger()->error(__VA_ARGS__)
#define APP_CRITICAL(...)  ::Titus::Log::GetClientLogger()->critical(__VA_ARGS__)

// TODO: Strip core logging from production builds
/*
* // If dist build
* 
* #define TE_CORE_TRACE(...)
* #define TE_CORE_INFO(...)
* #define TE_CORE_WARN(...)
* #define TE_CORE_ERROR(...)
* #define TE_CORE_CRITICAL(...)
*/
