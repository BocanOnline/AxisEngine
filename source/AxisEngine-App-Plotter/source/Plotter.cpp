//
// ProjectAxisEngine
// Plotter.cpp
//

#include <iostream>
#include <memory>

// Core Functionality
#include "AxisEngine.hpp"
#include "EntryPoint.hpp" // NOLINT

// User Added Functionality
#include "Modules/Actuator.hpp"
#include "Modules/Coolant.hpp"
#include "Modules/TemperatureSensor.hpp"
    
std::shared_ptr<Plotter::Module::Actuator> actuator;
std::shared_ptr<Plotter::Module::Coolant> coolant;
std::shared_ptr<Plotter::Module::TemperatureSensor> temperatureSensor;

void AxisEngine::Initialize() {
    
    std::cout << "[Plotter.cpp] start of Initialize()" << std::endl;

    actuator = std::make_shared<Plotter::Module::Actuator>();
    coolant = std::make_shared<Plotter::Module::Coolant>();
    temperatureSensor = std::make_shared<Plotter::Module::TemperatureSensor>();

    AxisEngine::AddModule(actuator);
    AxisEngine::AddModule(coolant);
    AxisEngine::AddModule(temperatureSensor);
    
    std::cout << "[Plotter.cpp] end of Initialize()..." << std::endl;
}

// The goal of this feature branch is to enable the user to add new events
// to this application without having to modify Core library code.
// This will initially be limited to only user defined modules, however I
// think that is okay for now.
// 
// An example of functionality would be a temperature sensor Module which reads
// a temperature of some tooling, and triggers an event when temperature exceeds
// or reaches a certain range. Another coolant Module is registered for that
// event and starts some function (activating coolant pump) on that event.
//
// Future: expose API endpoints to the Core::Modules to trigger user defined
// events.
//
// Currently there is an enum class for each event type and a corresponding
// function in Modules for each event. Each Module is capable of telling the 
// Kernel to CallEvent. When the Kernel CallEvent(), it cycles through it's
// data structure to call each Module registered for the events OnEvent()
// function.
//
// 1. Event interface class to be inherited by implemented Event child classes.
//      * Provides a ToString function for easy logging.
//      * Can be passed to the Kernel::CallEvent() as a parameter.
//
// 2. Data structure within Kernel for m_Hooks
//      * Stores Events, Module pointers that registered, and Function Pointers?
//        It may not be necessary to store a Module pointer if instead we 
//        store that Modules' appropriate Function Pointer to call.
//
// 3. Event Dispatcher within Kernel::CallEvent()
//      * Calls the appropriate functions for the event.
//
//4. AddEvent function within Kernel and AxisEngine API.
