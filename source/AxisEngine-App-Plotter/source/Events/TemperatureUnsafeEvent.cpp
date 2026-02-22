//
// ProjectAxisEngine
// TemperatureUnsafeEvent.cpp
//

#include <string>

#include "TemperatureUnsafeEvent.hpp"

Plotter::TemperatureUnsafeEvent::TemperatureUnsafeEvent() {}

Plotter::TemperatureUnsafeEvent::~TemperatureUnsafeEvent() {}

std::string Plotter::TemperatureUnsafeEvent::GetName() const {

    return "TEMPERATURE_UNSAFE";
}
