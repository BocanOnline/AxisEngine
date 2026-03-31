////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: Logger.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace Core {

    class Logger {

    public:
        static void Initialize(); 

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;

    };

} // namespace Core

#define AXIS_CORE_TRACE(...) SPDLOG_LOGGER_TRACE(Core::Logger::GetCoreLogger(), __VA_ARGS__)
#define AXIS_CORE_INFO (...) SPDLOG_LOGGER_INFO (Core::Logger::GetCoreLogger(), __VA_ARGS__)
#define AXIS_CORE_WARN (...) SPDLOG_LOGGER_WARN (Core::Logger::GetCoreLogger(), __VA_ARGS__)
#define AXIS_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(Core::Logger::GetCoreLogger(), __VA_ARGS__)
