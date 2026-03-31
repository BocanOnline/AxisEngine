////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: SlowTicker.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Events/IdleEvent.hpp"

#include "SlowTicker.hpp"


Core::SlowTicker::SlowTicker() {

    AXIS_CORE_TRACE("SlowTicker constructed");
}

Core::SlowTicker::~SlowTicker() {

    AXIS_CORE_TRACE("SlowTicker destroyed");
}
    
void Core::SlowTicker::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::SlowTicker::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);
    
    AXIS_CORE_TRACE("SlowTicker registered for OnIdle");
}

std::string Core::SlowTicker::GetName() const {

    return "SlowTicker";
}

void Core::SlowTicker::OnIdle(std::shared_ptr<void> argument) {

    AXIS_CORE_TRACE("SlowTicker called by OnIdle");
}

void Core::SlowTicker::RegisterForTask() {}
void Core::SlowTicker::Run() {}
void Core::SlowTicker::UnregisterForTask() {}
