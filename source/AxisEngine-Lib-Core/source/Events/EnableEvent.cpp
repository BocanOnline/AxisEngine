////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: EnableEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "EnableEvent.hpp"

Core::EnableEvent::EnableEvent() {}

Core::EnableEvent::~EnableEvent() {}

std::string Core::EnableEvent::GetName() const {

    return "ENABLE";
}
