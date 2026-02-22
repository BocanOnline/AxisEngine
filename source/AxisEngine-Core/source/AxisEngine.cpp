//
// ProjectAxisEngine
// AxisEngine.cpp
//

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
