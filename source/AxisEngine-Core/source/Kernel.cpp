////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: Kernel.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <unordered_map>

#include "Kernel.hpp"

#include "Events/IdleEvent.hpp"
#include "Events/MainLoopEvent.hpp"

#include "Module.hpp"
#include "Modules/SerialConsole.hpp"
#include "Modules/GcodeDispatch.hpp"
#include "Modules/SlowTicker.hpp"
#include "Modules/Robot.hpp"
#include "Modules/Conveyer.hpp"

Core::Kernel Core::Kernel::s_Instance;

Core::Kernel::Kernel() {
   
    std::cout << "[Kernel.cpp] Kernel created..." << std::endl; 
    std::cout << "[Kernel.cpp] Kernel constructor start..." << std::endl;
   
    serialconsole = std::make_shared<SerialConsole>();
    gcodedispatch = std::make_shared<GcodeDispatch>();
    slowticker    = std::make_shared<SlowTicker>();
    robot         = std::make_shared<Robot>();
    conveyer      = std::make_shared<Conveyer>();
   
    Core::Kernel::AddModule(serialconsole);
    Core::Kernel::AddModule(gcodedispatch);
    Core::Kernel::AddModule(slowticker);
    Core::Kernel::AddModule(robot);
    Core::Kernel::AddModule(conveyer);
    std::cout << "[Kernel.cpp] Kernel constructor end..." << std::endl; 

//    after these below function calls are implemented, I may move them to
//    the start of Run() to allow time to load the user modules before starting
//    any runtimes.
//
//    conveyer.start(robot.GetNumberRegisteredMotors());
//    slowticker.start();
}

Core::Kernel::~Kernel() {
    
    std::cout << "[Kernel.cpp] Kernel destroyed..." << std::endl;
}

void Core::Kernel::Run() {

    MainLoopEvent on_main_loop_event; 
    Core::Kernel::Get().CallEvent(on_main_loop_event, nullptr);

    IdleEvent on_idle_event;
    Core::Kernel::Get().CallEvent(on_idle_event, nullptr);
}

void Core::Kernel::AddModule(std::shared_ptr<Module> module) {
    
    std::cout << "[Kernel.cpp] Module added..." << std::endl;
    module->OnModuleLoaded();     
}

void Core::Kernel::RegisterForEvent(Event& event, 
        std::function<void(std::shared_ptr<void>)> function) {
    
    if (!Core::Kernel::HasEvent(event)) {
    
        std::cout << "[Kernel.cpp] " << 
            event.GetName() << " registering with Kernel..." << std::endl; 
        
        std::vector<std::function<void(std::shared_ptr<void>)>> function_list;
        function_list.emplace_back(function);
        m_CallbackTable.emplace(event.GetName(), function_list);
    } 
    else {
        
        m_CallbackTable.at(event.GetName()).emplace_back(function);        
    }
}

bool Core::Kernel::HasEvent(Event& event) {

    return m_CallbackTable.contains(event.GetName());
}

void Core::Kernel::CallEvent(Event& event, std::shared_ptr<void> argument) {

    if (!Core::Kernel::HasEvent(event)) {

        std::cerr << "[Kernel.cpp] Event not registered with the kernel..." << std::endl;
        return;
    }
    for (auto function : m_CallbackTable.at(event.GetName())) {
    
        function(argument); 
    }        
}
