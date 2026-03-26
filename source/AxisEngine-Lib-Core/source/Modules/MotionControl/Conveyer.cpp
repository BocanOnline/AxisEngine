////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Conveyer.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Kernel.hpp"

#include "Events/IdleEvent.hpp"

#include "Conveyer.hpp"


Core::Conveyer::Conveyer() {

}

Core::Conveyer::~Conveyer() {

}

void Core::Conveyer::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument){ this->Core::Conveyer::OnIdle(argument); };

    this->RegisterForEvent(on_idle_event, on_idle_function);

    std::cout << "[Conveyer.cpp] Conveyer registered for IdleEvent..." << std::endl;
}

void Core::Conveyer::OnIdle(std::shared_ptr<void> argument) {

}
