//
// ProjectAxisEngine
// Robot.cpp
//

#include <iostream>
#include <memory>

#include "../Kernel.hpp"

#include "../Events/IdleEvent.hpp"
#include "../Events/GcodeReceivedEvent.hpp"
#include "../Events/SecondTickEvent.hpp"

#include "Robot.hpp"


Core::Robot::Robot() {

    std::cout << "[Robot.cpp] Robot created..." << std::endl;
}

Core::Robot::~Robot() {

    std::cout << "[Robot.cpp] Robot destroyed..." << std::endl;
}
    
void Core::Robot::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Robot::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);

    std::cout << "[Robot.cpp] Robot registered for IdleEvent..." << std::endl;
    
    Core::GcodeReceivedEvent on_gcode_received_event;
    auto on_gcode_received_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Robot::OnGcodeReceived(argument); };
    this->RegisterForEvent(on_gcode_received_event, on_gcode_received_function);

    std::cout << "[Robot.cpp] Robot registered for GcodeReceivedEvent..." << std::endl;
    
    Core::SecondTickEvent on_second_tick_event;
    auto on_second_tick_function = [this](std::shared_ptr<void> argument)
                                { this->Core::Robot::OnSecondTick(argument); };
    this->RegisterForEvent(on_second_tick_event, on_second_tick_function);
    
    std::cout << "[Robot.cpp] Robot registered for SecondTickEvent..." << std::endl;
}

void Core::Robot::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by IdleEvent..." << std::endl;
}

void Core::Robot::OnGcodeReceived(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by GcodeReceivedEvent..." << std::endl; 
}

void Core::Robot::OnSecondTick(std::shared_ptr<void> argument) {

    std::cout << "[Robot.cpp] Robot called by SecondTickEvent..." << std::endl;
}
