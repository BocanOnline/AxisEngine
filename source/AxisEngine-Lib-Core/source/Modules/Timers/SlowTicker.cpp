////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SlowTicker.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

#include "Kernel.hpp"

#include "Events/IdleEvent.hpp"

#include "SlowTicker.hpp"


Core::SlowTicker::SlowTicker() {

    std::cout << "[SlowTicker.cpp] SlowTicker created..." << std::endl;
}

Core::SlowTicker::~SlowTicker() {

    std::cout << "[SlowTicker.cpp] SlowTicker destroyed..." << std::endl;
}
    
void Core::SlowTicker::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::SlowTicker::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);
    
    std::cout << "[SlowTicker.cpp] SlowTicker registered for IdleEvent..." << std::endl;
}

void Core::SlowTicker::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[SlowTicker.cpp] SlowTicker called by IdleEvent..." << std::endl; 
}

void Core::SlowTicker::RegisterForTask() {}
void Core::SlowTicker::Run() {}
void Core::SlowTicker::UnregisterForTask() {}
