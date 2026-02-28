////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: IdleEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "IdleEvent.hpp"

Core::IdleEvent::IdleEvent() {}

Core::IdleEvent::~IdleEvent() {}

std::string Core::IdleEvent::GetName() const {

    return "IDLE";
}
