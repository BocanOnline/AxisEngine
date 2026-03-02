////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Router
// file: TemperatureSensor.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

#include "AxisEngine.hpp"
#include "Events/IdleEvent.hpp"

#include "../Events/TemperatureUnsafeEvent.hpp"
#include "TemperatureSensor.hpp"

Router::Module::TemperatureSensor::TemperatureSensor() {

    std::cout << "[TemperatureSensor.cpp] TemperatureSensor created..." << std::endl;
}

Router::Module::TemperatureSensor::~TemperatureSensor() {

    std::cout << "[TemperatureSensor.cpp] TemperatureSensor destroyed..." << std::endl;
}
    
void Router::Module::TemperatureSensor::OnModuleLoaded() {

    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Router::Module::TemperatureSensor::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);

    std::cout << "[TemperatureSensor.cpp] TemperatureSensor registered for IdleEvent..." << std::endl;
}

void Router::Module::TemperatureSensor::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[TemperatureSensor.cpp] TemperatureSensor called by IdleEvent..." << std::endl; 
   
    TemperatureUnsafeEvent on_temperature_unsafe_event;
    AxisEngine::CallEvent(on_temperature_unsafe_event, nullptr);
}

