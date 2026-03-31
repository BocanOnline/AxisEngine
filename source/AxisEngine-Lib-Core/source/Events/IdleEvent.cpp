////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: IdleEvent.cpp
////////////////////////////////////////////////////////////////////////////////

#include "IdleEvent.hpp"

Core::IdleEvent::IdleEvent() {}

Core::IdleEvent::~IdleEvent() {}

std::string Core::IdleEvent::GetName() const {

    return "OnIdle";
}
