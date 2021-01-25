#pragma once
#include "LGCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


namespace LG
{
    class LG_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

    };

    //TODO: undef for distribution Builds.
#define LG_CORE_CRITICAL(...)   ::LG::Log::GetCoreLogger()->log(spdlog::level::critical, __VA_ARGS__);
#define LG_CORE_ERROR(...)      ::LG::Log::GetCoreLogger()->log(spdlog::level::err, __VA_ARGS__);
#define LG_CORE_WARN(...)       ::LG::Log::GetCoreLogger()->log(spdlog::level::warn, __VA_ARGS__);
#define LG_CORE_INFO(...)       ::LG::Log::GetCoreLogger()->log(spdlog::level::info, __VA_ARGS__);
#define LG_CORE_TRACE(...)      ::LG::Log::GetCoreLogger()->log(spdlog::level::trace, __VA_ARGS__);

#define LG_CRITICAL(...)        ::LG::Log::GetClientLogger()->log(spdlog::level::critical, __VA_ARGS__);
#define LG_ERROR(...)           ::LG::Log::GetClientLogger()->log(spdlog::level::err, __VA_ARGS__);
#define LG_WARN(...)            ::LG::Log::GetClientLogger()->log(spdlog::level::warn, __VA_ARGS__);
#define LG_INFO(...)            ::LG::Log::GetClientLogger()->log(spdlog::level::info, __VA_ARGS__);
#define LG_TRACE(...)           ::LG::Log::GetClientLogger()->log(spdlog::level::trace, __VA_ARGS__);

}
