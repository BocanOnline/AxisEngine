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

#include "../Module.hpp"

namespace Core {

    class StepTicker : public Module {

    public:
        StepTicker();
        virtual ~StepTicker() override;
        
        virtual void OnModuleLoaded() override;

        void OnIdle(std::shared_ptr<void> argument) override;
    };

} // namespace Core
