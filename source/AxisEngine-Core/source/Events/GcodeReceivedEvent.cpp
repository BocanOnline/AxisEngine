//
// ProjectAxisEngine
// GcodeReceivedEvent.cpp
//

#include <string>

#include "GcodeReceivedEvent.hpp"

Core::GcodeReceivedEvent::GcodeReceivedEvent() {}

Core::GcodeReceivedEvent::~GcodeReceivedEvent() {}

std::string Core::GcodeReceivedEvent::GetName() const {

    return "GCODE_RECEIVED";
}
