////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SerialConsole.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

#include "../Kernel.hpp"

#include "../Events/MainLoopEvent.hpp"
#include "../Events/IdleEvent.hpp"

#include "SerialConsole.hpp"


Core::SerialConsole::SerialConsole() {

    std::cout << "[SerialConsole.cpp] SerialConsole created..." << std::endl;
}

Core::SerialConsole::~SerialConsole() {

    std::cout << "[SerialConsole.cpp] SerialConsole destroyed..." << std::endl;
}
    
void Core::SerialConsole::OnModuleLoaded() {

    Core::MainLoopEvent on_main_loop_event;
    auto on_main_loop_function = [this](std::shared_ptr<void> argument)
                                { this->Core::SerialConsole::OnMainLoop(argument); };
    this->RegisterForEvent(on_main_loop_event, on_main_loop_function);
    
    std::cout << "[SerialConsole.cpp] SerialConsole registered for MainLoopEvent..." << std::endl;
    
    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument)
                                { this->Core::SerialConsole::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function);
    
    std::cout << "[SerialConsole.cpp] SerialConsole registered for IdleEvent..." << std::endl;

}

void Core::SerialConsole::OnMainLoop(std::shared_ptr<void> argument) {

    std::cout << "[SerialConsole.cpp] SerialConsole called by MainLoopEvent..." << std::endl;
}

void Core::SerialConsole::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[SerialConsole.cpp] SerialConsole called by IdleEvent..." << std::endl;
}
