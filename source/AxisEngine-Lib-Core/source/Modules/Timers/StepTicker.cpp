////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: StepTicker.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Events/IdleEvent.hpp"

#include "StepTicker.hpp"


Core::StepTicker::StepTicker() {

    AXIS_CORE_TRACE("StepTicker constructed");
}

Core::StepTicker::~StepTicker() {

    AXIS_CORE_TRACE("StepTicker destroyed");
}
    
void Core::StepTicker::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::StepTicker::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);
    
    AXIS_CORE_TRACE("StepTicker registered for OnIdle");
}

std::string Core::StepTicker::GetName() const {

    return "StepTicker";
}

void Core::StepTicker::OnIdle(std::shared_ptr<void> argument) {

    AXIS_CORE_TRACE("StepTicker called by OnIdle");
}

void Core::StepTicker::RegisterForTask() {}
void Core::StepTicker::Run() {}
void Core::StepTicker::UnregisterForTask() {}

