////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-App-Printer
// file: Printer.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

// Core Functionality
#include "AxisEngine.hpp"

// User Added Functionality

void AxisEngine::Initialize() {
    
    std::cout << "[Printer.cpp] start of Initialize()" << std::endl;

    // actuator = std::make_shared<Plotter::Module::Actuator>();
    // coolant = std::make_shared<Plotter::Module::Coolant>();
    // temperatureSensor = std::make_shared<Plotter::Module::TemperatureSensor>();

    // AxisEngine::AddModule(actuator);
    // AxisEngine::AddModule(coolant);
    // AxisEngine::AddModule(temperatureSensor);
    
    std::cout << "[Printer.cpp] end of Initialize()..." << std::endl;
}
