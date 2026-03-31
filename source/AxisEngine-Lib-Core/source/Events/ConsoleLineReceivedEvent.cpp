////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: ConsoleLineReceivedEvent.cpp
////////////////////////////////////////////////////////////////////////////////

#include "ConsoleLineReceivedEvent.hpp"

Core::ConsoleLineReceivedEvent::ConsoleLineReceivedEvent() {}

Core::ConsoleLineReceivedEvent::~ConsoleLineReceivedEvent() {}

std::string Core::ConsoleLineReceivedEvent::GetName() const {

    return "OnConsoleLineReceived";
}
