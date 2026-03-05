////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: AxisEngine.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "AxisEngine.hpp"
#include "Kernel.hpp"
#include "Module.hpp"
#include "Event.hpp"

namespace AxisEngine {

    void AddModule(std::shared_ptr<Core::Module> module) { // NOLINT
            
        return Core::Kernel::Get().AddModule(module);
    }
    void CallEvent(Core::Event& event, std::shared_ptr<void> argument) { // NOLINT

        return Core::Kernel::Get().CallEvent(event, argument);
    }
    void Run() { // NOLINT

        return Core::Kernel::Get().Run();
    }
}

#include <iostream>

int main(int argc, char** argv) { // NOLINT

    std::cout << "[AxisEngine.hpp] Start of main function..." << std::endl;
    
    AxisEngine::Initialize();

    AxisEngine::Run();
    
    std::cout << "[AxisEngine.hpp] End of main function..." << std::endl;
    return 0;
}
