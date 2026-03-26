////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SimpleShell.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "Module.hpp"

namespace Core {

    class SimpleShell : public Module {

    public:
        SimpleShell();
        virtual ~SimpleShell() override;
        
        virtual void OnModuleLoaded() override;

        void OnConsoleLineReceived(std::shared_ptr<void> argument) override;
    };

} // namespace Core
