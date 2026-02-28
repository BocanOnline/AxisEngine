////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: EntryPoint.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <iostream>

#include "AxisEngine.hpp"

int main(int argc, char** argv) { // NOLINT

    std::cout << "[EntryPoint.hpp] Start of main function..." << std::endl;
    
    AxisEngine::Initialize();

    AxisEngine::Run();
    
    std::cout << "[EntryPoint.hpp] End of main function..." << std::endl;
    return 0;
}

