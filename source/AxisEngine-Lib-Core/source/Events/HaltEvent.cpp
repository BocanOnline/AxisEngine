////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: HaltEvent.cpp
////////////////////////////////////////////////////////////////////////////////

#include "HaltEvent.hpp"

Core::HaltEvent::HaltEvent() {}

Core::HaltEvent::~HaltEvent() {}

std::string Core::HaltEvent::GetName() const {

    return "OnHalt";
}
