////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: ConsoleLineReceivedEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "ConsoleLineReceivedEvent.hpp"

Core::ConsoleLineReceivedEvent::ConsoleLineReceivedEvent() {}

Core::ConsoleLineReceivedEvent::~ConsoleLineReceivedEvent() {}

std::string Core::ConsoleLineReceivedEvent::GetName() const {

    return "CONSOLE_LINE_RECEIVED";
}
