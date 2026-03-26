////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Core
// file: StepTicker.hpp
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "Module.hpp"
#include "Worker.hpp"

namespace Core {

    class StepTicker : public Module, Worker {

    public:
        StepTicker();
        virtual ~StepTicker() override;
       
        // Module
        virtual void OnModuleLoaded() override;
        void OnIdle(std::shared_ptr<void> argument) override;
        
        // Worker
        virtual void RegisterForTask() override;
        virtual void Run() override;
        virtual void UnregisterForTask() override;
    };

} // namespace Core
