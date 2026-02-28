////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Plotter
// file: TemperatureUnsafeEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "TemperatureUnsafeEvent.hpp"

Plotter::TemperatureUnsafeEvent::TemperatureUnsafeEvent() {}

Plotter::TemperatureUnsafeEvent::~TemperatureUnsafeEvent() {}

std::string Plotter::TemperatureUnsafeEvent::GetName() const {

    return "TEMPERATURE_UNSAFE";
}
