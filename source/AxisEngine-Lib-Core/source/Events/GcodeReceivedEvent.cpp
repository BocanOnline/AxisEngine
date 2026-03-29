////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: GcodeReceivedEvent.cpp
////////////////////////////////////////////////////////////////////////////////

#include "GcodeReceivedEvent.hpp"

Core::GcodeReceivedEvent::GcodeReceivedEvent() {}

Core::GcodeReceivedEvent::~GcodeReceivedEvent() {}

std::string Core::GcodeReceivedEvent::GetName() const {

    return "GCODE_RECEIVED";
}
