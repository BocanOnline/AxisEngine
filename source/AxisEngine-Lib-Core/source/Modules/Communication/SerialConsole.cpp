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

#include "Kernel.hpp"

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

    std::cout << "[SerialConsole.cpp] SerialConsole created..." << std::endl;
}

Core::SerialConsole::~SerialConsole() {

    std::cout << "[SerialConsole.cpp] SerialConsole destroyed..." << std::endl;
}
    
void Core::SerialConsole::OnModuleLoaded() {

    Core::MainLoopEvent on_main_loop_event;
    auto on_main_loop_function = [this](std::shared_ptr<void> argument){ this->Core::SerialConsole::OnMainLoop(argument); };
    this->RegisterForEvent(on_main_loop_event, on_main_loop_function); 
    std::cout << "[SerialConsole.cpp] SerialConsole registered for MainLoopEvent..." << std::endl;
    
    Core::IdleEvent on_idle_event;
    auto on_idle_function = [this](std::shared_ptr<void> argument){ this->Core::SerialConsole::OnIdle(argument); };
    this->RegisterForEvent(on_idle_event, on_idle_function); 
    std::cout << "[SerialConsole.cpp] SerialConsole registered for IdleEvent..." << std::endl;

}

void Core::SerialConsole::OnMainLoop(std::shared_ptr<void> argument) {
    
    std::cout << "[SerialConsole.cpp] SerialConsole called by MainLoopEvent..." << std::endl; 

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
    
        std::cout << "[SerialConsole.cpp] SerialMessage Received..." << std::endl;
        std::cout << "[SerialConsole.cpp] " << m_LineBuffer << std::endl;

        Core::ConsoleLineReceivedEvent on_console_line_received_event;
        Core::Kernel::Get().CallEvent(on_console_line_received_event, message);
    }
}

void Core::SerialConsole::OnIdle(std::shared_ptr<void> argument) {

    std::cout << "[SerialConsole.cpp] SerialConsole called by IdleEvent..." << std::endl;

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
    
        std::cout << "[SerialConsole.cpp] m_LineBuffer empty..." << std::endl;
        
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
