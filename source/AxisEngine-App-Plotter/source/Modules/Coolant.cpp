////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Plotter
// file: Coolant.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

#include "AxisEngine.hpp"

#include "../Events/TemperatureUnsafeEvent.hpp"
#include "Coolant.hpp"

Plotter::Module::Coolant::Coolant() {

    std::cout << "[Coolant.cpp] Coolant created..." << std::endl;
}

Plotter::Module::Coolant::~Coolant() {

    std::cout << "[Coolant.cpp] Coolant destroyed..." << std::endl;
}
    
void Plotter::Module::Coolant::OnModuleLoaded() {

    Plotter::TemperatureUnsafeEvent on_temperature_unsafe_event;
    auto on_temperature_unsafe_function = [this](std::shared_ptr<void> argument)
                                { this->Plotter::Module::Coolant::OnTemperatureUnsafe(argument); };
    this->RegisterForEvent(on_temperature_unsafe_event, on_temperature_unsafe_function);

    std::cout << "[Coolant.cpp] Coolant registered for TemperatureUnsafeEvent..." << std::endl;
}

void Plotter::Module::Coolant::OnTemperatureUnsafe(std::shared_ptr<void> argument) {

    std::cout << "[Coolant.cpp] Coolant called by TemperatureUnsafeEvent..." << std::endl; 
}
