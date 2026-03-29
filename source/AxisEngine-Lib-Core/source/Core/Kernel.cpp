////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: Kernel.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>

#include "Kernel.hpp"

#include "Events/IdleEvent.hpp"
#include "Events/MainLoopEvent.hpp"

#include "Module.hpp"
#include "Modules/Communication/SerialConsole.hpp"
#include "Modules/Communication/GcodeDispatch.hpp"
#include "Modules/Communication/SimpleShell.hpp"
#include "Modules/MotionControl/Robot.hpp"
#include "Modules/MotionControl/Conveyer.hpp"
#include "Modules/Timers/SlowTicker.hpp"
#include "Modules/Timers/StepTicker.hpp"

Core::Kernel Core::Kernel::s_Instance;

Core::Kernel::Kernel() {
   
    std::cout << "[Kernel.cpp] Kernel created..." << std::endl; 
    std::cout << "[Kernel.cpp] Kernel constructor start..." << std::endl;
   
    m_SerialConsole = std::make_shared<SerialConsole>();
    m_GcodeDispatch = std::make_shared<GcodeDispatch>();
    m_SimpleShell   = std::make_shared<SimpleShell>();
    m_Robot         = std::make_shared<Robot>();
    m_Conveyer      = std::make_shared<Conveyer>();
    m_SlowTicker    = std::make_shared<SlowTicker>();
    m_StepTicker    = std::make_shared<StepTicker>();
   
    Core::Kernel::AddModule(m_SerialConsole);
    Core::Kernel::AddModule(m_GcodeDispatch);
    Core::Kernel::AddModule(m_SimpleShell);
    Core::Kernel::AddModule(m_Robot);
    Core::Kernel::AddModule(m_Conveyer);
    Core::Kernel::AddModule(m_SlowTicker);
    Core::Kernel::AddModule(m_StepTicker);
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

    m_Conveyer->Start(m_Robot->GetNumberRegisteredMotors());

    while(!m_SerialConsole->ReceivedExitCommand()) {

        MainLoopEvent on_main_loop_event; 
        Core::Kernel::Get().CallEvent(on_main_loop_event, nullptr);

        IdleEvent on_idle_event;
        Core::Kernel::Get().CallEvent(on_idle_event, nullptr);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Core::Kernel::AddModule(std::shared_ptr<Module> module) {
    
    std::cout << "[Kernel.cpp] Module added..." << std::endl;
    module->OnModuleLoaded();     
}

void Core::Kernel::RegisterForEvent(Event& event, std::function<void(std::shared_ptr<void>)> function) {
    
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

float Core::Kernel::GetStepTickerFrequency() {

    return m_StepTicker->GetFrequency();
}
