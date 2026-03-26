////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: MainLoopEvent.cpp
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "MainLoopEvent.hpp"

Core::MainLoopEvent::MainLoopEvent() {}

Core::MainLoopEvent::~MainLoopEvent() {}

std::string Core::MainLoopEvent::GetName() const {

    return "MAIN_LOOP";
}
