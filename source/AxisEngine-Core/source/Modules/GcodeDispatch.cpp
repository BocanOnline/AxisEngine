//
// ProjectAxisEngine
// GcodeDispatch.cpp
//

#include <iostream>
#include <memory>

#include "../Kernel.hpp"

#include "../Events/ConsoleLineReceivedEvent.hpp"

#include "GcodeDispatch.hpp"


Core::GcodeDispatch::GcodeDispatch() {

    std::cout << "[GcodeDispatch.cpp] GcodeDispatch created..." << std::endl;
}

Core::GcodeDispatch::~GcodeDispatch() {

    std::cout << "[GcodeDispatch.cpp] GcodeDispatch destroyed..." << std::endl;
}
    
void Core::GcodeDispatch::OnModuleLoaded() {

    Core::ConsoleLineReceivedEvent on_console_line_received_event;
    auto on_console_line_received_function = [this](std::shared_ptr<void> argument)
                                { this->Core::GcodeDispatch::OnConsoleLineReceived(argument); };
    this->RegisterForEvent(on_console_line_received_event, on_console_line_received_function);

    std::cout << "[GcodeDispatch.cpp] GcodeDispatch registered for ConsoleLineReceivedEvent..." << std::endl;
}

void Core::GcodeDispatch::OnConsoleLineReceived(std::shared_ptr<void> argument) {

    std::cout << "[GcodeDispatch.cpp] GcodeDispatch called by ConsoleLineReceivedEvent..." << std::endl; 
}
