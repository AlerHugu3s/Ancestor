#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ancestor {
	class ANCESTOR_API Log
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

//core log macros
#define AC_CORE_ERROR(...)	::Ancestor::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AC_CORE_WARN(...)	::Ancestor::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AC_CORE_INFO(...)	::Ancestor::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AC_CORE_TRACE(...)	::Ancestor::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AC_CORE_FATAL(...)	::Ancestor::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macros
#define AC_ERROR(...)	::Ancestor::Log::GetClientLogger()->error(__VA_ARGS__)
#define AC_WARN(...)	::Ancestor::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AC_INFO(...)	::Ancestor::Log::GetClientLogger()->info(__VA_ARGS__)
#define AC_TRACE(...)	::Ancestor::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AC_FATAL(...)	::Ancestor::Log::GetClientLogger()->fatal(__VA_ARGS__)
