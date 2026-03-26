////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: NetworkStream.cpp
////////////////////////////////////////////////////////////////////////////////

#include <string>

#include "NetworkStream.hpp"

Core::NetworkStream::NetworkStream() {}

Core::NetworkStream::~NetworkStream() {}
       
char Core::NetworkStream::GetChar() {

    return '\0';
}

std::string Core::NetworkStream::GetLine() {

    return "\0";
}

bool Core::NetworkStream::PutChar() {

    return false;
}

bool Core::NetworkStream::PutLine() {

    return false;
}
