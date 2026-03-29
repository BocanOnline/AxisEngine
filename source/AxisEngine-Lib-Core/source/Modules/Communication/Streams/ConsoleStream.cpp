////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: ConsoleStream.cpp
////////////////////////////////////////////////////////////////////////////////

#include "ConsoleStream.hpp"

Core::ConsoleStream::ConsoleStream() {}

Core::ConsoleStream::~ConsoleStream() {}
       
char Core::ConsoleStream::GetChar() {

    return '\0';
}

std::string Core::ConsoleStream::GetLine() {

    std::string line;

    std::getline(std::cin, line);
    return line;
}

bool Core::ConsoleStream::PutChar() {

    return false;
}

bool Core::ConsoleStream::PutLine() {

    return false;
}
////////////////////////////////////////////////////////////////////////////////
// TODO
// [ ] implement threads to prevent GetLine from blocking execution
////////////////////////////////////////////////////////////////////////////////
