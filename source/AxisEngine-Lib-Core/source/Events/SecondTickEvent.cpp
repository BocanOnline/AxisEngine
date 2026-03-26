////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SecondTickEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "SecondTickEvent.hpp"

Core::SecondTickEvent::SecondTickEvent() {}

Core::SecondTickEvent::~SecondTickEvent() {}

std::string Core::SecondTickEvent::GetName() const {

    return "SECOND_TICK";
}
