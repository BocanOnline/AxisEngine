////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: AxisEngine.cpp
////////////////////////////////////////////////////////////////////////////////

#include "AxisEngine.hpp"

namespace AxisEngine {

    void AddModule(std::shared_ptr<Core::Module> module) {
            
        return Core::Kernel::Get().AddModule(module);
    }
    void CallEvent(Core::Event& event, std::shared_ptr<void> argument) {

        return Core::Kernel::Get().CallEvent(event, argument);
    }
    void Run() { // NOLINT

        return Core::Kernel::Get().Run();
    }
}

int main(int argc, char** argv) {

    AXIS_CORE_TRACE("Start of Main function");
    
    AxisEngine::Initialize();

    AxisEngine::Run();
    
    AXIS_CORE_TRACE("End of Main function");
    return 0;
}
