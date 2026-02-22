//
// ProjectAxisEngine
// Conveyer.cpp
//

#include <iostream>
#include <memory>
#include <functional>

#include "../Kernel.hpp"

#include "../Events/IdleEvent.hpp"
#include "../Events/HaltEvent.hpp"

#include "Conveyer.hpp"


Core::Conveyer::Conveyer() {

    std::cout << "[Conveyer.cpp] Conveyer created..." << std::endl;
}

Core::Conveyer::~Conveyer() {

    std::cout << "[Conveyer.cpp] Conveyer destroyed..." << std::endl;
}
    
void Core::Conveyer::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Conveyer::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);

    std::cout << "[Conveyer.cpp] Conveyer registered for IdleEvent..." << std::endl;

    Core::HaltEvent on_halt_event;
    auto on_halt_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Conveyer::OnHalt(argument); };
    this->RegisterForEvent(on_halt_event, on_halt_function);
    
    std::cout << "[Conveyer.cpp] Conveyer registered for HaltEvent..." << std::endl;
}

void Core::Conveyer::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[Conveyer.cpp] Conveyer called by IdleEvent..." << std::endl; 
}

void Core::Conveyer::OnHalt(std::shared_ptr<void> argument) {

    std::cout << "[Conveyer.cpp] Conveyer called by HaltEvent..." << std::endl; 
}
