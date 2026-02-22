//
// ProjectAxisEngine
// Module.cpp
//

#include "Kernel.hpp"
#include "Module.hpp"

void Core::Module::RegisterForEvent(Core::Event &event, 
        std::function<void(std::shared_ptr<void>)> function) {

    Core::Kernel::Get().RegisterForEvent(event, function);
}

