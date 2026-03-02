////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Router
// file: TemperatureUnsafeEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "TemperatureUnsafeEvent.hpp"

Router::TemperatureUnsafeEvent::TemperatureUnsafeEvent() {}

Router::TemperatureUnsafeEvent::~TemperatureUnsafeEvent() {}

std::string Router::TemperatureUnsafeEvent::GetName() const {

    return "TEMPERATURE_UNSAFE";
}
