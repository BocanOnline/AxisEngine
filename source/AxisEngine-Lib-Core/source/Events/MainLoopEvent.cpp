////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: MainLoopEvent.cpp
////////////////////////////////////////////////////////////////////////////////

#include "MainLoopEvent.hpp"

Core::MainLoopEvent::MainLoopEvent() {}

Core::MainLoopEvent::~MainLoopEvent() {}

std::string Core::MainLoopEvent::GetName() const {

    return "OnMainLoop";
}
