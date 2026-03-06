////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: FileStream.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

#include "FileStream.hpp"

Core::FileStream::FileStream() {

    file.open("test/gcode/router-cylinder.gcode");
}

Core::FileStream::~FileStream() {

    file.close();
}
       
char Core::FileStream::GetChar() {

    return '\0';
}

std::string Core::FileStream::GetLine() {
    
    std::string line;

    if(file.is_open()) {

        std::getline(file, line);
    } else {

        std::cerr << "[FileStream.cpp] Unable to open file..." << line << std::endl;
    }
    return line;
}

bool Core::FileStream::PutChar() {

    return false;
}

bool Core::FileStream::PutLine() {

    return false;
}
