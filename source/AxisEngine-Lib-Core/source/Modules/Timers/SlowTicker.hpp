////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: SlowTicker.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "Module.hpp"
#include "Worker.hpp"

namespace Core {

    class SlowTicker : public Module, Worker {

    public:
        SlowTicker();
        virtual ~SlowTicker() override;
   
        // Module
        virtual void OnModuleLoaded() override;
        virtual void OnIdle(std::shared_ptr<void> argument) override;

        // Worker
        virtual void RegisterForTask() override;
        virtual void Run() override;
        virtual void UnregisterForTask() override;
    
    };

} // namespace Core
