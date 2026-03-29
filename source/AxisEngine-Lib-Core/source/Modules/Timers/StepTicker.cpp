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

    std::cout << "[StepTicker.cpp] StepTicker created..." << std::endl;
}

Core::StepTicker::~StepTicker() {

    std::cout << "[StepTicker.cpp] StepTicker destroyed..." << std::endl;
}
    
void Core::StepTicker::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::StepTicker::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);
    
    std::cout << "[StepTicker.cpp] StepTicker registered for IdleEvent..." << std::endl;
}

void Core::StepTicker::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[StepTicker.cpp] StepTicker called by IdleEvent..." << std::endl; 
}

void Core::StepTicker::RegisterForTask() {}
void Core::StepTicker::Run() {}
void Core::StepTicker::UnregisterForTask() {}
