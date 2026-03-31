////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: GcodeDispatch.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Events/ConsoleLineReceivedEvent.hpp"
#include "Events/GcodeReceivedEvent.hpp"

#include "Modules/Communication/Utils/SerialMessage.hpp"
#include "Modules/Communication/Utils/Gcode.hpp"

#include "GcodeDispatch.hpp"


Core::GcodeDispatch::GcodeDispatch() {

    AXIS_CORE_TRACE("GcodeDispatch constructed");
}

Core::GcodeDispatch::~GcodeDispatch() {

    AXIS_CORE_TRACE("GcodeDispatch destroyed");
}
    
void Core::GcodeDispatch::OnModuleLoaded() {

    Core::ConsoleLineReceivedEvent on_console_line_received_event;
    auto on_console_line_received_function = [this](std::shared_ptr<void> argument){ this->Core::GcodeDispatch::OnConsoleLineReceived(argument); };
    this->RegisterForEvent(on_console_line_received_event, on_console_line_received_function);
    AXIS_CORE_TRACE("GcodeDispatch registered for OnConsoleLineReceived");
}
        
std::string Core::GcodeDispatch::GetName() const {

    return "GcodeDispatch";
}

void Core::GcodeDispatch::OnConsoleLineReceived(std::shared_ptr<void> argument) {

    AXIS_CORE_TRACE("GcodeDispatch called by OnConsoleLineReceived");

    std::shared_ptr<Core::SerialMessage> message = std::static_pointer_cast<Core::SerialMessage>(argument);

    if(message->Message.front() != 'G' && message->Message.front() != 'M') {

        AXIS_CORE_TRACE("SerialMessage is not a supported g-code");
        return;
    }

    std::string raw_message = message->Message;
    std::shared_ptr<Core::Gcode> gcode = std::make_shared<Core::Gcode>();

    std::string::size_type n;
    std::string::size_type i;

    // find and remove comments    
    n = raw_message.find(';');
    if(std::string::npos != n) {
        raw_message.erase(n, (raw_message.length() - n));
    }

    // remove trailing white space
    while(raw_message.back() == ' ') {
        raw_message.pop_back();
    }

    // parse commands and arguments
    do {
        i = 0;
        n = raw_message.find(' ');

        std::string sub_string;

        if(std::string::npos != n) {
            sub_string = raw_message.substr(i, n - i);
            raw_message.erase(i, (n - i) + 1);
        } else {
            sub_string  = raw_message;
        }
        
        if(sub_string.at(i) == 'G') {
            gcode->Has_G = true;
            sub_string.erase(i, 1);
            gcode->AddWord('G', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'M') {
            gcode->Has_M = true;
            sub_string.erase(i, 1);
            gcode->AddWord('M', std::stof(sub_string, &i)); 
        }
        else if(sub_string.at(i) == 'X') {
            gcode->Has_X = true;
            sub_string.erase(i, 1);
            gcode->AddWord('X', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'Y') {
            gcode->Has_Y = true;
            sub_string.erase(i, 1);
            gcode->AddWord('Y', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'Z') {
            gcode->Has_Z = true;
            sub_string.erase(i, 1);
            gcode->AddWord('Z', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'E') {
            gcode->Has_E = true;
            sub_string.erase(i, 1);
            gcode->AddWord('E', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'A') {
            gcode->Has_Z = true;
            sub_string.erase(i, 1);
            gcode->AddWord('A', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'B') {
            gcode->Has_B = true;
            sub_string.erase(i, 1);
            gcode->AddWord('B', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'C') {
            gcode->Has_C = true;
            sub_string.erase(i, 1);
            gcode->AddWord('C', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'F') {
            gcode->Has_F = true;
            sub_string.erase(i, 1);
            gcode->AddWord('F', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'S') {
            gcode->Has_S = true;
            sub_string.erase(i, 1);
            gcode->AddWord('S', std::stof(sub_string, &i));
        }
        else {
            char prefix = sub_string.at(i);
            sub_string.erase(i, 1);
            gcode->AddWord(prefix, std::stof(sub_string, &i));
        }
    } while(std::string::npos != n);

    if(gcode->Has_G) { AXIS_CORE_TRACE("Gcode Received: G{}", gcode->GetValue_I('G'));}
    if(gcode->Has_M) { AXIS_CORE_TRACE("Gcode Received: M{}", gcode->GetValue_I('M'));}
    
    Core::GcodeReceivedEvent on_gcode_received_event;
    Core::Kernel::Get().CallEvent(on_gcode_received_event, gcode);
}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] add error checking to g-code parsing code
////////////////////////////////////////////////////////////////////////////////
