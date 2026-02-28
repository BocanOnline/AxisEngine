////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Plotter
// file: Actuator.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

#include "Actuator.hpp"
#include "Events/GcodeReceivedEvent.hpp"

Plotter::Module::Actuator::Actuator() {

    std::cout << "[Actuator.cpp] Actuator created..." << std::endl;
}

Plotter::Module::Actuator::~Actuator() {

    std::cout << "[Actuator.cpp] Actuator destroyed..." << std::endl;
}
    
void Plotter::Module::Actuator::OnModuleLoaded() {

    Core::GcodeReceivedEvent on_gcode_received_event;
    auto on_gcode_received_function = [this](std::shared_ptr<void> argument)
                                { this->Plotter::Module::Actuator::OnGcodeReceived(argument); };
    this->RegisterForEvent(on_gcode_received_event, on_gcode_received_function);

    std::cout << "[Actuator.cpp] Actuator registered for GcodeReceivedEvent..." << std::endl;
}

void Plotter::Module::Actuator::OnGcodeReceived(std::shared_ptr<void> argument) {

    std::cout << "[Actuator.cpp] Actuator called by GcodeReceivedEvent..." << std::endl; 
}
