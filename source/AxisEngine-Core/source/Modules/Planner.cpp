////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Planner.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

#include "../Kernel.hpp"

#include "../Events/IdleEvent.hpp"
#include "../Events/SecondTickEvent.hpp"

#include "Planner.hpp"


Core::Planner::Planner() {

    std::cout << "[Planner.cpp] Planner created..." << std::endl;
}

Core::Planner::~Planner() {

    std::cout << "[Planner.cpp] Planner destroyed..." << std::endl;
}
    
void Core::Planner::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Planner::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);

    std::cout << "[Planner.cpp] Planner registered for IdleEvent..." << std::endl;
    
    Core::SecondTickEvent on_second_tick_event;
    auto on_second_tick_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Planner::OnSecondTick(argument); };
    this->RegisterForEvent(on_second_tick_event, on_second_tick_function);
    
    std::cout << "[Planner.cpp] Planner registered for SecondTickEvent..." << std::endl;
}

void Core::Planner::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[Planner.cpp] Planner called by IdleEvent..." << std::endl;
}

void Core::Planner::OnSecondTick(std::shared_ptr<void> argument) {

    std::cout << "[Planner.cpp] Planner called by SecondTickEvent..." << std::endl;
}
