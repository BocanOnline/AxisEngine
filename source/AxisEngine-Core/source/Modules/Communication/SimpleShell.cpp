////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SimpleShell.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>


#include "Events/ConsoleLineReceivedEvent.hpp"

#include "Utils/SerialMessage.hpp"

#include "SimpleShell.hpp"


Core::SimpleShell::SimpleShell() {

    std::cout << "[SimpleShell.cpp] SimpleShell created..." << std::endl;
}

Core::SimpleShell::~SimpleShell() {

    std::cout << "[SimpleShell.cpp] SimpleShell destroyed..." << std::endl;
}
    
void Core::SimpleShell::OnModuleLoaded() {

    Core::ConsoleLineReceivedEvent on_console_line_received_event;
    auto on_console_line_received_function = [this](std::shared_ptr<void> argument)
                                { this->Core::SimpleShell::OnConsoleLineReceived(argument); };
    this->RegisterForEvent(on_console_line_received_event, on_console_line_received_function);

    std::cout << "[SimpleShell.cpp] SimpleShell registered for ConsoleLineReceivedEvent..." << std::endl;
}

void Core::SimpleShell::OnConsoleLineReceived(std::shared_ptr<void> argument) {

    std::cout << "[SimpleShell.cpp] SimpleShell called by ConsoleLineReceivedEvent..." << std::endl; 

    std::shared_ptr<Core::SerialMessage> message = std::static_pointer_cast<Core::SerialMessage>(argument);

    if(message->message.front() != '$') {

        std::cout << "[SimpleShell.cpp] SerialMessage is not a supported SimpleShell Command..." << std::endl;
        return;
    }
    
    std::cout << "[SimpleShell.cpp] SimpleShell Command..." << std::endl;

}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] implement SimpleShell commands
////////////////////////////////////////////////////////////////////////////////
