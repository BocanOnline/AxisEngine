////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SimpleShell.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Events/ConsoleLineReceivedEvent.hpp"

#include "Modules/Communication/Utils/SerialMessage.hpp"

#include "SimpleShell.hpp"


Core::SimpleShell::SimpleShell() {

    AXIS_CORE_TRACE("SimpleShell constructed");
}

Core::SimpleShell::~SimpleShell() {

    AXIS_CORE_TRACE("SimpleShell destroyed");
}
    
void Core::SimpleShell::OnModuleLoaded() {

    Core::ConsoleLineReceivedEvent on_console_line_received_event;
    auto on_console_line_received_function = [this](std::shared_ptr<void> argument){ this->Core::SimpleShell::OnConsoleLineReceived(argument); };
    this->RegisterForEvent(on_console_line_received_event, on_console_line_received_function);
    AXIS_CORE_TRACE("SimpleShell registered for OnConsoleLineReceived");
}

std::string Core::SimpleShell::GetName() const {

    return "SimpleShell";
}

void Core::SimpleShell::OnConsoleLineReceived(std::shared_ptr<void> argument) {

    AXIS_CORE_TRACE("SimpleShell called by OnConsoleLineReceived");

    std::shared_ptr<Core::SerialMessage> message = std::static_pointer_cast<Core::SerialMessage>(argument);

    if(message->Message.front() != '$') {

        AXIS_CORE_TRACE("SerialMessage is not a supported SimpleShell command");
        return;
    }
    
    AXIS_CORE_TRACE("SimpleShell command received");

}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] implement SimpleShell commands
////////////////////////////////////////////////////////////////////////////////
