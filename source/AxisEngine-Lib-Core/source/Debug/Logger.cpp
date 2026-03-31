////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: Logger.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Logger.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Core::Logger::s_CoreLogger;

void Core::Logger::Initialize() {

    spdlog::set_pattern("%^[%T] %n::%s: %v%$");

    s_CoreLogger = spdlog::stdout_color_mt("AxisEngine::Core");
    s_CoreLogger->set_level(spdlog::level::trace);
}
