////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Router
// file: Router.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

// Core Functionality
#include "AxisEngine.hpp"

// User Added Functionality
#include "Modules/Actuator.hpp"
#include "Modules/Coolant.hpp"
#include "Modules/TemperatureSensor.hpp"
    
std::shared_ptr<Router::Module::Actuator> actuator;
std::shared_ptr<Router::Module::Coolant> coolant;
std::shared_ptr<Router::Module::TemperatureSensor> temperatureSensor;

void AxisEngine::Initialize() {
    
    std::cout << "[Router.cpp] start of Initialize()" << std::endl;

    // actuator = std::make_shared<Plotter::Module::Actuator>();
    // coolant = std::make_shared<Plotter::Module::Coolant>();
    // temperatureSensor = std::make_shared<Plotter::Module::TemperatureSensor>();

    // AxisEngine::AddModule(actuator);
    // AxisEngine::AddModule(coolant);
    // AxisEngine::AddModule(temperatureSensor);
    
    std::cout << "[Router.cpp] end of Initialize()..." << std::endl;
}
