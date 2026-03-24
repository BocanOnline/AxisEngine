////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: GcodeDispatch.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <memory>

#include "Kernel.hpp"

#include "Events/ConsoleLineReceivedEvent.hpp"
#include "Events/GcodeReceivedEvent.hpp"

#include "Utils/SerialMessage.hpp"
#include "Utils/Gcode.hpp"

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

    std::shared_ptr<Core::SerialMessage> message = std::static_pointer_cast<Core::SerialMessage>(argument);

    if(message->message.front() != 'G' && message->message.front() != 'M') {

        std::cout << "[GcodeDispatch.cpp] SerialMessage is not a supported GcodeCommand..." << std::endl;
        return;
    }

    std::string raw_message = message->message;
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
            gcode->has_g = true;
            sub_string.erase(i, 1);
            gcode->add_word('G', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'M') {
            gcode->has_m = true;
            sub_string.erase(i, 1);
            gcode->add_word('M', std::stof(sub_string, &i)); 
        }
        else if(sub_string.at(i) == 'X') {
            gcode->has_x = true;
            sub_string.erase(i, 1);
            gcode->add_word('X', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'Y') {
            gcode->has_y = true;
            sub_string.erase(i, 1);
            gcode->add_word('Y', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'Z') {
            gcode->has_z = true;
            sub_string.erase(i, 1);
            gcode->add_word('Z', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'E') {
            gcode->has_e = true;
            sub_string.erase(i, 1);
            gcode->add_word('E', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'A') {
            gcode->has_z = true;
            sub_string.erase(i, 1);
            gcode->add_word('A', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'B') {
            gcode->has_b = true;
            sub_string.erase(i, 1);
            gcode->add_word('B', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'C') {
            gcode->has_c = true;
            sub_string.erase(i, 1);
            gcode->add_word('C', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'F') {
            gcode->has_f = true;
            sub_string.erase(i, 1);
            gcode->add_word('F', std::stof(sub_string, &i));
        }
        else if(sub_string.at(i) == 'S') {
            gcode->has_s = true;
            sub_string.erase(i, 1);
            gcode->add_word('S', std::stof(sub_string, &i));
        }
        else {
            char prefix = sub_string.at(i);
            sub_string.erase(i, 1);
            gcode->add_word(prefix, std::stof(sub_string, &i));
        }
    } while(std::string::npos != n);

    std::cout << "[GcodeDispatch.cpp] Gcode created..." << std::endl;
    std::cout << "[GcodeDispatch.cpp] Command: ";
    if(gcode->has_g) { std::cout << "G" << gcode->get_ivalue('G') << std::endl; }
    if(gcode->has_m) { std::cout << "M" << gcode->get_ivalue('M') << std::endl; }
    for(const auto& [key, value] : gcode->word) {
        std::cout << "[GcodeDispatch.cpp] Argument: " << key << value << std::endl;
    }
    
    Core::GcodeReceivedEvent on_gcode_received_event;
    Core::Kernel::Get().CallEvent(on_gcode_received_event, gcode);
}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] add error checking to g-code parsing code
////////////////////////////////////////////////////////////////////////////////
