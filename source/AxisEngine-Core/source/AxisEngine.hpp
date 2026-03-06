////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: AxisEngine.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Module.hpp"
#include "Event.hpp"

namespace AxisEngine {

    void Initialize();

    void AddModule(std::shared_ptr<Core::Module> module);
            
    void CallEvent(Core::Event& event, std::shared_ptr<void> argument);

    void Run();

} // namespace AxisEngiine
