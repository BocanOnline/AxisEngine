////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SerialConsole.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Events/ConsoleLineReceivedEvent.hpp"
#include "Events/MainLoopEvent.hpp"
#include "Events/HaltEvent.hpp"
#include "Events/IdleEvent.hpp"

#include "Modules/Communication/Utils/SerialMessage.hpp"

#include "Modules/Communication/Streams/ConsoleStream.hpp"
#include "Modules/Communication/Streams/FileStream.hpp"
#include "Modules/Communication/Streams/NetworkStream.hpp"

#include "SerialConsole.hpp"


Core::SerialConsole::SerialConsole() {

    int stream_config = 2;

    switch(stream_config) {
        case 1:
            m_Stream = std::make_shared<Core::ConsoleStream>();
            break;
        case 2:
            m_Stream = std::make_shared<Core::FileStream>();
            break;
        case 3:
            m_Stream = std::make_shared<Core::NetworkStream>();
            break;
        default:
    }

    AXIS_CORE_TRACE("SerialConsole constructed");
}

Core::SerialConsole::~SerialConsole() {

    AXIS_CORE_TRACE("SerialConsole destroyed");
}
    
void Core::SerialConsole::OnModuleLoaded() {

    Core::MainLoopEvent on_main_loop_event;
    auto on_main_loop_function = [this](std::shared_ptr<void> argument){ this->Core::SerialConsole::OnMainLoop(argument); };
    this->RegisterForEvent(on_main_loop_event, on_main_loop_function); 
    AXIS_CORE_TRACE("SerialConsole registered for OnMainLoop");
    
    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument){ this->Core::SerialConsole::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function); 
    AXIS_CORE_TRACE("SerialConsole registered for OnIdle");

}

std::string Core::SerialConsole::GetName() const {

    return "SerialConsole";
}

void Core::SerialConsole::OnMainLoop(std::shared_ptr<void> argument) {
    
    AXIS_CORE_TRACE("SerialConsole called by OnMainLoop");

    m_LineBuffer = m_Stream->GetLine();

    if(this->HasChar('\x1B')) {

        m_HaltFlag = true;
    }
    if(this->HasChar('?')) {

        m_QueryFlag = true;
    }
    if(this->HasChar('Q') || this->HasChar('q')) {

        m_ExitFlag = true;
    }
    if(this->HasLine()) {

        std::shared_ptr<Core::SerialMessage> message = std::make_shared<Core::SerialMessage>();
        message->Message = m_LineBuffer; 
    
        AXIS_CORE_TRACE("SerialMessage Received: {}", m_LineBuffer);

        Core::ConsoleLineReceivedEvent on_console_line_received_event;
        Core::Kernel::Get().CallEvent(on_console_line_received_event, message);
    }
}

void Core::SerialConsole::OnIdle(std::shared_ptr<void> argument) {

    AXIS_CORE_TRACE("SerialConsole called by OnIdle");

    if(m_HaltFlag) {

        Core::HaltEvent on_halt_event;
        Core::Kernel::Get().CallEvent(on_halt_event, argument);
    }
}

void Core::SerialConsole::RegisterForTask() {}
void Core::SerialConsole::Run() {}
void Core::SerialConsole::UnregisterForTask() {}

bool Core::SerialConsole::HasLine() {

    if(m_LineBuffer.empty()) {
    
        AXIS_CORE_TRACE("Received line is empty");
        
        return false;
    }
    return true;
}

bool Core::SerialConsole::HasChar(char letter) {
  
    if(m_LineBuffer.find(letter) != std::string::npos) {
        
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] add configurable stream and file address
// [ ] flesh out Streams and Child Class methods
// [ ] implement NetworkStream
////////////////////////////////////////////////////////////////////////////////
